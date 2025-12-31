project = 'da4cpp'
copyright = '2025, Slaven Glumac'
author = 'Slaven Glumac'
release = '0.0.1'

extensions = ['breathe', 'exhale']

# Breathe configuration
breathe_projects = {"da4cpp": "../build/docs/doxygen/xml"}
breathe_default_project = "da4cpp"

# Exhale configuration - MANUAL MODE
exhale_args = {
    "containmentFolder": "./api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "API Reference",
    "doxygenStripFromPath": "..",
    
    # CRITICAL: Manual mode
    "exhaleExecutesDoxygen": False,  # You run Doxygen separately
    
    # Optional but useful
    "createTreeView": True,
    "verboseBuild": True,
}

html_theme = 'sphinx_rtd_theme'

