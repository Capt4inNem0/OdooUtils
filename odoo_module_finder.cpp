#ifndef ODOO_MODULE_FINDER
#define ODOO_MODULE_FINDER

#include <iostream>
#include <filesystem>
#include <set>
#include <stack>
#include <string>
#include <boost/algorithm/string/join.hpp>
namespace fs = std::filesystem;


bool is_odoo_module(const fs::path &path) {
    fs::path manifest_path = path / "__manifest__.py";
    return fs::exists(manifest_path);
}


int main(int argc, char *argv[]) {
    fs::path p = fs::canonical("./");
    if (argc > 1) {
        std::string arg_path = argv[1];
        if (fs::exists(arg_path) && fs::is_directory(arg_path)) {
            p = fs::canonical(arg_path);
        } else {
            std::cout << "Invalid path" << std::endl;
            return 1;
        }
    }
    
    std::set<std::string> odoo_modules;
    std::stack<fs::path> stack;
    stack.push(p);
    if (fs::exists(p) && fs::is_directory(p)) {
        while (!stack.empty()) {
            fs::path current = stack.top();
            stack.pop();
            if (is_odoo_module(current)) {
                odoo_modules.insert(current.parent_path());
            } else {
                for (const auto &entry : fs::directory_iterator(current)) {
                    if (fs::is_directory(entry.path())) {
                        stack.push(entry.path());
                    }
                }
            }
        }
    } else {
        std::cout << "Path does not exist or is not a directory" << std::endl;
    }
    if (odoo_modules.empty()) {
        std::cout << "No Odoo modules found" << std::endl;
    } else {
        std::cout << boost::algorithm::join(odoo_modules, ", ") << std::endl;
    } 
    return 0;
}

#endif

