'''
Library of object types used to dump valid C++ code
'''
from URAnalysis.AnalysisTools.autocode.cppformat import cpp_format
from pdb import set_trace
import os

_templates_dir = os.path.join(
   os.environ['CMSSW_BASE'],
   'src/URAnalysis/AnalysisTools/python/autocode/templates'
)
def get_template(name):
   '''Gets the template from
   AnalysisTools/python/templates'''
   return open(
      os.path.join(
         _templates_dir,
         '%s.template' % name
         )
      ).read()

class BranchMeta(object):
   '''Class that handles TTree branch 
   autocode operations'''
   type_map = {
      'D' : 'Double_t', 
      'F' : 'Float_t' , 
      'I' : 'Int_t', 
      'i' : 'UInt_t', 
      'L' : 'Long64_t', 
      'l' : 'ULong64_t', 
      'B' : 'Char_t', 
      'b' : 'UChar_t', 
      'S' : 'Short_t', 
      's' : 'UShort_t', 
      'O': 'Bool_t'
      }
   def __init__(self, branch):
      self.name = branch.GetName()
      self.is_object = '_' in self.name
      self.var_public = not self.is_object
      self.var = self.name.split('/')[0]
      if self.is_object:
         self.var += '_'
      if hasattr(branch, 'GetTypeName'):
         self.type = branch.GetTypeName()
         self.is_vector = True
      else:
         root_type = self.name.split('/')[1]
         self.is_vector = False
         try:
            self.type = BranchMeta.type_map[root_type]
         except:
            raise ValueError(
               'Branch type, %s, does not match'
               ' any known type!' % root_type)

   def cpp_var(self):
      'C++ variable'
      ptr = '*' if self.is_vector else ''
      return '%s %s%s;' % (self.type, ptr, self.var)
   
   def cpp_init(self):
      'C++ constructor init'
      return '%s(0)' % self.var

   def cpp_set_branch(self, tname='tree_'):
      'C++ activate and set branch'
      return '{TREE}->SetBranchStatus("{NAME}", 1);' \
         ' {TREE}->SetBranchAddress("{NAME}", &{VAR});'.format(
         TREE=tname, NAME=self.name, VAR=self.var)

class ObjectMeta(object):
   '''Class that handles autocode objects 
   operations. Objects are groups of branches
   that start with the same pattern <object name>_'''
   cpp_template = get_template('loadObject')
   vgetter_template = get_template('getVObj')
   
   def __init__(self, prefix, branches):
      self.var_public = False
      self.prefix = prefix
      self.name = self.prefix.title()
      self.obj_container= prefix+'_'
      self.branches = branches
      self.load_var = 'are_%s_loaded_' % self.prefix
      self.is_vector = all(
         i.is_vector for i in self.branches
         )
      self.as_struct = ObjStruct(self)

   def cpp_var(self):
      'C++ variable'
      loader = 'bool %s;' % self.load_var
      ptr = 'vector<%s> %s;' if self.is_vector else \
         '%s %s;'
      ptr = ptr % (self.as_struct.name, self.obj_container)
      return '%s\n%s' % (loader, ptr)

   def cpp_init(self):
      'C++ constructor init'
      return '%s(0), %s()' % \
         (self.load_var, self.obj_container)

   def cpp_clear(self):
      'C++ clear object'
      if self.is_vector:
         return '%s.clear();' % self.obj_container

   def cpp_load(self, tname='tree_'):
      '''C++ activate and set branch
      made in a separate function to 
      allow customized load of the 
      objects'''
      return cpp_format(
         ObjectMeta.cpp_template,
         NAME=self.name,
         LOAD_VAR=self.load_var,
         BRANCH_SETTING='\n'.join(
            i.cpp_set_branch(tname) \
               for i in self.branches
            )
         )

   def cpp_obj_getter(self):
      '''C++ function to retreive the 
      object from the event'''
      if self.is_vector:
         return self._vobj_getter()
      else:
         return self._single_getter()
   
   def _vobj_getter(self):
      #make iterators
      #self.as_struct.name
      iterators = '\n'.join(
         'auto it_{var} = {var}->cbegin();'.format(
            var = i.var) for i in self.branches
         )
      end_cond = 'it_{var} != {var}->cend()'.format(
         var=self.branches[0].var
         )
      it_increment = ', '.join(
         '++it_%s' % i.var for i in self.branches
         )
      it_dump = ', '.join(
         '*it_%s' % i.var for i in self.branches
         )
      return cpp_format(
         ObjectMeta.vgetter_template,
         OBJ_VAR=self.obj_container,
         RET_TYPE = self.as_struct.name,
         NAME = self.prefix,
         ITRATORS = iterators,
         END_COND = end_cond,
         IT_INCREMENT = it_increment,
         IT_DUMP = it_dump,
         )


class ObjStruct(object):
   '''handles the struct definition of an object'''
   cpp_template = get_template('ObjectStruct')
   class Member(object):
      'a data member'
      def __init__(self, branch):
         #FIXME this class should be made more 
         #resilient against strange naming/variable
         #behaviors!
         self.var = branch.var.split('_')[1] #remove '_'
         self.var += '_'
         #remove the vector<> if any FIXME for v< v<int> >
         self.type= branch.type.split('<')[1].strip('>')

      def cpp_var(self):
         'C++ variable'
         return 'const %s *%s;' % (self.type, self.var)
   
      def cpp_getter(self):
         'C++ variable'
         return '%s %s() const {return *%s;}' % (self.type, self.var[:-1], self.var)

      def cpp_input(self):
         'C++ var input'
         return 'const %s &i_%s' % (self.type, self.var) 

      def cpp_init(self):
         'C++ constructor init'
         return '{VAR}(&i_{VAR})'.format(VAR=self.var)

      def cpp_void_init(self):
         'C++ constructor init'
         return '{VAR}(0)'.format(VAR=self.var)

   def __init__(self, obj):
      self.name = obj.name
      if obj.is_vector:
         self.name = self.name[:-1] #remove 's'
      self.members = [
         ObjStruct.Member(i) for i in obj.branches
         ]

   def cpp_dump(self):
      members = '\n'.join(
         i.cpp_var() for i in self.members
         )
      inputs = ','.join(
         i.cpp_input() for i in self.members
         )
      init = ',\n'.join(
         i.cpp_init() for i in self.members
         )
      void_init = ',\n'.join(
         i.cpp_void_init() for i in self.members
         )
      getters = '\n'.join(
         i.cpp_getter() for i in self.members
         )
      return cpp_format(
         ObjStruct.cpp_template,
         NAME=self.name,
         MEMBERS=members,
         INPUTS=inputs,
         MEMBERS_INIT=init,
         MEMBERS_VOID_INIT=void_init,
         GETTERS=getters,
         )

   def cpp_link(self):
      return '#pragma link C++ class %s+;' % self.name

class StreamerMeta(object):
   '''Class handles the full streamer translation
   to C++ code'''
   cpp_template = get_template('Streamer')

   def __init__(self, branches, objects):
      self.branches = branches
      self.objects = objects

   def cpp_dump(self):
      pub_members_list = '\n'.join(
         i.cpp_var() for i in self.branches + 
         self.objects if i.var_public
         )
      priv_members_list = '\n'.join(
         i.cpp_var() for i in self.branches +
         self.objects if not i.var_public
         )
      members_init = ',\n'.join(
         i.cpp_init() for i in self.branches + 
         self.objects
         )
      branch_setting = '\n'.join(
         i.cpp_set_branch() for i in self.branches \
            if not i.is_object
         )
      load_methods = '\n'.join(
         i.cpp_load() for i in self.objects
         )
      structs = '\n'.join(
         i.as_struct.cpp_dump() for i in self.objects
         )
      obj_getters = '\n'.join(
         i.cpp_obj_getter() for i in self.objects
         )
      destruct = '\n'.join(
         i.cpp_clear() for i in self.objects
         )
      links = '\n'.join(
         i.as_struct.cpp_link() for i in self.objects
         )

      return cpp_format(
         StreamerMeta.cpp_template,
         OBJECTS_STRUCTS=structs,
         PUBLIC_MEMBER_LIST=pub_members_list,
         PRIVATE_MEMBER_LIST=priv_members_list,
         MEMBER_INIT=members_init,
         BRANCH_SETTING=branch_setting,
         LOAD_METHODS=load_methods,
         OBJ_GETTERS=obj_getters,
         EVT_CLEAR=destruct
         )
   

class LinkDefMeta(object):
   '''Class handles the LinkDef translation
   to C++ code'''
   cpp_template = get_template('LinkDef')

   def __init__(self, objects):
      self.objects = objects
      
   def cpp_dump(self):
      vlinks = '\n'.join(
         '#pragma link C++ class vector<%s>+;' % i.as_struct.name \
            for i in self.objects if i.is_vector
         )
      obj_links = '\n'.join(
          '#pragma link C++ class %s+;' % i.as_struct.name \
             for i in self.objects
         )
      return cpp_format(
         LinkDefMeta.cpp_template,
         LINK_VOBJS=vlinks,
         LINK_OBJS=obj_links,
         )
