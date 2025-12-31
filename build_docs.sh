#!/bin/bash
# pip install -r requirements_docs.txt
REPO=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
DOXYGEN_BUILD=$REPO/build/docs/doxygen
DOCS=$REPO/docs
DOCS_BUILD=$REPO/docs/_build

set -e  # Exit on any error

echo "Repo: $REPO"
echo "Docs: $DOCS_DIR"

# 1. Generate Doxygen XML
echo "Generating Doxygen XML..."
cd "$REPO"
mkdir -p "$DOXYGEN_BUILD"
doxygen Doxyfile

# 2. Build Sphinx documentation
echo "Building Sphinx documentation..."
cd "$DOCS"
sphinx-build -b html . _build

echo "Documentation built in $DOCS_BUILD"

