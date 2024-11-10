from sphinx.builders.latex import LaTeXBuilder
from sphinx.writers.latex import LaTeXTranslator

class CustomLaTeXTranslator(LaTeXTranslator):
    def visit_tabular_col_spec(self, node):
        pass  # Override to prevent default table spec

    def depart_tabular_col_spec(self, node):
        pass

    def visit_sphinxtab(self, node):
        self.body.append('\n\\begin{mdframed}[linewidth=1pt,linecolor=gray!40]\n')
        self.body.append('\\textbf{%s}\n\n' % node['tab-label'])

    def depart_sphinxtab(self, node):
        self.body.append('\\end{mdframed}\n')

class CustomLaTeXBuilder(LaTeXBuilder):
    name = 'custom_latex'
    format = 'latex'
    default_translator_class = CustomLaTeXTranslator

def setup(app):
    app.add_builder(CustomLaTeXBuilder)
    return {
        'version': '1.0',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }