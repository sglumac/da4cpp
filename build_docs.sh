#!/bin/bash
# pip install -r requirements_docs.txt
REPO=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DOCS=$REPO/docs
DOCS_BUILD=$SCRIPT_DIR/docs/_build

set -e  # Exit on any error

echo "Repo: $REPO"
echo "Docs: $DOCS_DIR"

# 1. Generate Doxygen XML
echo "Generating Doxygen XML..."
cd "$REPO"
doxygen Doxyfile

# 2. Build Sphinx documentation
echo "Building Sphinx documentation..."
cd "$DOCS"
sphinx-build -b html . _build

echo "Documentation built in $DOCS_BUILD"

