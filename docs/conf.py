project = 'da4cpp'
copyright = '2025, Slaven Glumac'
author = 'Slaven Glumac'
release = '0.0.1'

# General configuration
templates_path = ['_templates']
exclude_patterns = []

extensions = [
    'breathe',
    'exhale'
]

# Breathe configuration
breathe_projects = {"da4cpp": "../build/docs/doxygen/xml"}
breathe_default_project = "da4cpp"

# Exhale configuration
exhale_args = {
    "containmentFolder": "./api",
    "rootFileName": "library_root.rst",
    "doxygenStripFromPath": "../",
    "createTreeView": True,
    "exhaleExecutesDoxygen": False,
}

# HTML output
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
 
