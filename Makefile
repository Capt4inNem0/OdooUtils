
CXX="g++"
CXXFLAGS="-std=c++23"

all: main

main: odoo_module_finder.cpp
	$(CXX) $(CXXFLAGS) -o odoo_module_finder odoo_module_finder.cpp

clean:
	rm -f odoo_module_finder

install: main
	cp odoo_module_finder /usr/local/bin
	chmod +x /usr/local/bin/odoo_module_finder

uninstall:
	rm -f /usr/local/bin/odoo_module_finder

