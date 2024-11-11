# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import os, sys
sys.path.append(os.path.abspath('.'))


project = 'C++ for Scientists and Engineers'
copyright = '2024, Jonas Lindemann'
author = 'Jonas Lindemann'
release = '0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.imgconverter',
    'sphinx_copybutton',
    'sphinx_design',
    'sphinx_tabs.tabs'
    #'custom_latex_builder'
    ]

image_converter = "C:\\Program Files\\ImageMagick-7.0.10-Q16-HDRI\\magick.exe"
image_converter_args=["-density", "300"]

numfig = True

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# -- Options for literalinclude ------------------------------------------------


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_material'

html_show_copyright = True

html_show_sourcelink = True
html_sidebars = {
    "**": ["logo-text.html", "globaltoc.html", "localtoc.html", "searchbox.html"]
}

html_theme_options = {

    # Set the name of the project to appear in the navigation.
    'nav_title': 'C++ for Scientists and Engineers',

    # Specify a base_url used to generate sitemap.xml. If not
    # specified, then no sitemap will be built.
    'base_url': 'https://project.github.io/project',

    # Set the color and the accent color
    'color_primary': 'yellow',
    'color_accent': 'yellow',

    # Set the repo location to get a badge with stats
    'repo_url': 'https://github.com/lunarc/cpp_course',
    'repo_name': 'C++ for Scientists and Engineers',

    # Visible levels of the global TOC; -1 means unlimited
    'globaltoc_depth': 2,
    # If False, expand all TOC entries
    'globaltoc_collapse': True,
    # If True, show hidden TOC entries
    'globaltoc_includehidden': True,
    'master_doc': False,
    'logo_icon': '&#xe869',

}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
html_css_files = ['custom.css']

# -- Options for LaTeX output ------------------------------------------------

# LaTeX configuration
# LaTeX configuration
# LaTeX configuration
latex_engine = 'xelatex'

latex_elements = {
    'papersize': 'c5paper',
    'pointsize': '10pt',
    
    'passoptionstopackages': r'''
\PassOptionsToPackage{svgnames}{xcolor}
''',
    
    'preamble': r'''
\usepackage{fontspec}
\usepackage{listings}
\usepackage{fancyvrb}  % Added this package
\usepackage[most]{tcolorbox}
\usepackage{environ}
\usepackage{mdframed}

% Main fonts
\setmainfont{Cambria}           % For body text
\setsansfont{Calibri}          % For headers

% Monospace font for code with explicit size
\setmonofont{Berkeley Mono}[
    Scale=0.75,
    NFSSFamily=codefont
]

% Configure listings package for code blocks
\lstset{
    basicstyle=\scriptsize\ttfamily,
    columns=flexible,
    keepspaces=true,
    fontadjust=true,
    backgroundcolor=\color{codebg},
    frame=none,
    breaklines=true
}

% Define colors
\definecolor{codebg}{RGB}{245,245,245}

% Rest of the preamble settings
\usepackage[titles]{tocloft}
\cftsetpnumwidth {1.25cm}\cftsetrmarg{1.5cm}
\setlength{\cftchapnumwidth}{0.75cm}
\setlength{\cftsecindent}{\cftchapnumwidth}
\setlength{\cftsecnumwidth}{1.25cm}
''',

    'fontpkg': '',
    'sphinxsetup': '''
        TitleColor=DarkGoldenrod,
        verbatimwithframe=false,
        verbatimwrapslines=false,
        verbatimsep=5pt,
        verbatimborder=0pt,
        VerbatimColor={RGB}{245,245,245}
    ''',
    'fncychap': r'\usepackage[Bjornstrup]{fncychap}',
    'printindex': r'\footnotesize\raggedright\printindex',
}
latex_show_urls = 'footnote'
latex_show_pagerefs = True
latex_domain_indices = True