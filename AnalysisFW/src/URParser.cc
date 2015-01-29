#ifndef URParser_cxx
#define URParser_cxx

//FIXME: add include
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "URParser.h"
#include "Logger.h"

opts::options_description & URParser::optionGroup(std::string groupName, std::string desc, Visibility vis)
{
  //std::map<std::string, OptionGroup>::iterator 
  auto found = opts_.find(groupName);
  if(found == opts_.end())
  {
    opts_.insert(std::make_pair(groupName, OptionGroup(groupName, desc, vis)));
    found = opts_.find(groupName);
  }
  return found->second.value;
}

void URParser::help()
{
  for(auto it = opts_.begin(); it != opts_.end(); ++it)
  {
    //use fatal as we always want it to be displayed
    Logger::log().fatal() << it->second.help << std::endl
	      << "Available: ";

    switch(it->second.visibility)
    {
    case ALL: Logger::log().fatal() << "everywhere" << std::endl; break;
    case CLI: Logger::log().fatal() << "Command line only" << std::endl; break;
    case CFG: Logger::log().fatal() << "Configuration file only" << std::endl; break;
    }
    Logger::log().fatal() << it->second.value << std::endl;
  }
}

void URParser::parseArguments()
{
  //avoid repeating parsing, it's dangerous!
  if(parsed_) return;
  parsed_ = true;
  opts::options_description cli_opts;
  for(auto it = opts_.begin(); it != opts_.end(); ++it)
    if(it->second.visibility == ALL || it->second.visibility == CLI)
      cli_opts.add(it->second.value);

  store(opts::command_line_parser(argc_, argv_).
	options(cli_opts).positional(args_).run(), vmap_);
  notify(vmap_);

  if (vmap_.count("help")) {
    help();
    std::exit(0);
  }

  if(vmap_.count("config"))
  {
    std::string config_file = vmap_["config"].as<std::string>();
    std::ifstream ifs(config_file.c_str());
    if(!ifs)
    {
      Logger::log().fatal() << "can not open config file: " << config_file << std::endl;
      throw 42;
    }
    else
    {
      opts::options_description cfg_opts;
      for(auto it = opts_.begin(); it != opts_.end(); ++it)
	if(it->second.visibility == ALL || it->second.visibility == CFG)
	  cfg_opts.add(it->second.value);

      store(parse_config_file(ifs, cfg_opts), vmap_);
      notify(vmap_);
    }
  }
}

#endif
