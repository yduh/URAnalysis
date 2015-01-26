#ifndef FileOpener_h
#define FileOpener_h



class FileOpener
{
  public:
    TChain* OpenFile(const std::string sampleName, TChain* tree = 0, TChain* metadataTree = 0);
};

#endif // FileOpener_h
