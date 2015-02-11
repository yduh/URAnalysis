tools = "#{$fwk_dir}/rake/tools.rb"
require tools

rule ".exe" => [
    #the input .cc
    proc {|target| target.sub(%r{(ENV['URA_PROJECT']/)?bin/(.*).exe}, "#{ENV['URA_PROJECT']}/\\2.cc")},
    proc { "#{ENV['URA_PROJECT']}/lib/.lib_timestamp"},
    proc { "#{ENV['URA']}/AnalysisFW/lib/.lib_timestamp"}] do |t|
  puts t.investigation
  project_dir = ENV['URA_PROJECT']
  fwk_dir = ENV['URA']+'/AnalysisFW'
  local_libs = Dir.glob("#{project_dir}/lib/*.*o")
  fwk_libs = Dir.glob("#{fwk_dir}/lib/*.*o")
  prj_libs = Array[ENV.fetch('URA_PROJECT_LIBS', '')]
  
  local_includes = "#{project_dir}/interface/"
  fwk_includes = "#{fwk_dir}/interface/"
  
  sh compile_string([local_includes, fwk_includes],local_libs+fwk_libs+prj_libs, t.prerequisites[0], t.name)
  #"g++ -I#{local_includes} -I#{fwk_includes} `root-config --cflags` `root-config --libs` -lboost_program_options #{libs} #{t.prerequisites[0]} -o #{t.name}"
end

rule ".cfg" do |t|
  sh "touch #{t.name}"
  puts t.investigation
end

rule ".root" => [ 
    # The analyzer executable
    proc {|targ| targ.sub(%r{results/.*/(.*)/.*root}, "bin/\\1.exe")},
    # The cfg
    proc {|targ| targ.sub(%r{results/.*/(.*)/.*root}, "\\1.cfg")},
    # The sample file list .txt file
    proc {|targ| targ.sub(%r{results/(.*)/.*/(.*).root}, "inputs/\\1/\\2.txt")} ] do |t|
  # Make the output directory
  sh "mkdir -p `dirname #{t.name}`"
  workers = ENV.fetch('URA_NTHREADS', 2)
  executable = File.basename(t.prerequisites[0])
  cfg = t.prerequisites[1]
  inputs = t.prerequisites[2]
  sh "time #{executable} #{inputs} #{t.name} -c  #{cfg} --threads #{workers}"
end

task :analyze, [:analyzer] do |t, args|
  bname = File.basename(args.analyzer).split('.')[0]
  jobid = ENV['jobid']
  Dir.glob("inputs/#{jobid}/*.txt").each do |input_file|
    sample = File.basename(input_file).split('.')[0]
    #puts "results/#{jobid}/#{bname}/#{sample}.root"
    Rake::Task["results/#{jobid}/#{bname}/#{sample}.root"].invoke
  end
end
