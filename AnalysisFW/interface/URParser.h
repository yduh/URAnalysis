class URParser
{
  public:
    // Not publicly accessible
//     URParser() : argc_(0),argv_(0) {};
//     URParser(const int argc, const char* argv) : argc_(argc), argv_(argv){};

    void parseArguments(const int argc, const char* argv){};

    // This must be a singleton
    static URParser& instance();
    
    template<typename T>
    void addOption<T>(const std::string& optionName, const T defaultValue, const std::string help = 0);
    template<typename T>
    T getOption<T>(const std::string& optionName) const;

  private:
    int argc_;
    char* argv_;
    // <key,<type,value> >
    static std::map<std::string,std::pair<std::string,std::string > > optionsMap_;
};
