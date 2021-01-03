#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <getopt.h>
#include <map>
#include <string>
#include <vector>


const std::string upper(const std::string& s);


class ArgumentError : public std::runtime_error
{
public:
    ArgumentError(const std::string what) : std::runtime_error(what) {}
};


class Arg
{
private:
    const option option_;
    const std::string metavar;
    const std::string help;

public:
    Arg(option& option_, std::string help, std::string metavar)
        : option_(option_),
          metavar(metavar),
          help(help) { }

    const std::string get_help(void) const { return help; }
    const std::string get_metavar(void) const { return metavar; }
    const option get_option(void) const { return option_; }
};


struct Args
{
    std::map<std::string, int> flags;  // flag name -> number of occurrences
    std::multimap<std::string, std::string> options;
    std::vector<std::string> positionals;
};


class ArgumentParser
{
private:
    const int _argc;
    char** _argv;
    std::vector<Arg> _arguments;
    std::string _description;
    std::vector<std::string> _examples;
    std::vector<option> _long_options;

    std::string _get_short_options(void);

public:
    ArgumentParser(int argc, char** argv);
    void print_help(void);
    void print_usage(void);
    void add_argument(const char* long_, const char short_, const int argument_required, const std::string& help);
    void add_argument(const char* long_, const char short_, const int argument_required, const std::string& help, const std::string& metavar);
    void add_description(const std::string& description);
    void add_example(const std::string& example);
    Args parse_args(void);
};


#endif
