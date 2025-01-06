# Variables
SCONS = scons
GODOT = godot
DOXYGEN = doxygen
DOXYFILE = Doxyfile
SRC_DIR = src
TESTLIB_DIR = testlib
DEMO_DIR = demo
TESTLIB_SO = $(TESTLIB_DIR)/testlib.so
DEMO_BIN_SO = $(DEMO_DIR)/bin/testlib.so
DOCS_DIR = ./docs/html
TEST_SCRIPT = test.gd

# Default target
.PHONY: all
all: help

# Build the module
.PHONY: build_module
build_module:
	$(SCONS)

# Clean the module
.PHONY: clean_module
clean_module:
	rm -f $(SRC_DIR)/*.os

# Build the test library
.PHONY: build_test_library
build_test_library:
	$(MAKE) -C $(TESTLIB_DIR) testlib.so
	cp $(TESTLIB_SO) $(DEMO_BIN_SO)

# Clean the test library
.PHONY: clean_test_library
clean_test_library:
	rm -f $(DEMO_BIN_SO)

# Execute Godot test
.PHONY: execute_gd_test
execute_gd_test:
	cd $(DEMO_DIR) && $(GODOT) --no-window --headless --script $(TEST_SCRIPT)

# Create Doxygen documentation
.PHONY: create_doxygen_docs
create_doxygen_docs:
	$(DOXYGEN) $(DOXYFILE)

# Clean Doxygen documentation
.PHONY: clean_doxygen_docs
clean_doxygen_docs:
	rm -rf $(DOCS_DIR)

# Prepare for publishing
.PHONY: prep_for_publish
prep_for_publish: clean_module clean_test_library clean_doxygen_docs create_doxygen_docs

# Help message
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build_module         - Build the module using scons"
	@echo "  clean_module         - Clean compiled module files"
	@echo "  build_test_library   - Build the test library and copy it to the demo/bin folder"
	@echo "  clean_test_library   - Clean the test library files"
	@echo "  execute_gd_test      - Run the test.gd script with Godot in headless mode"
	@echo "  create_doxygen_docs  - Generate the Doxygen documentation"
	@echo "  clean_doxygen_docs   - Remove the generated Doxygen documentation"
	@echo "  prep_for_publish     - Clean and recreate everything for publishing"
