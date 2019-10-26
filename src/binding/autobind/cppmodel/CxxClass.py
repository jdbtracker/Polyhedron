from .CxxNode import CxxNode

class CxxClass(CxxNode):
    
    def __init__(self, sourceObject, parent = None):
        CxxNode.__init__(self, sourceObject, parent)

    def get_inheritance_hierarchy(self):
        pass
    # def function

    def namespaceBlock(self, body):
        namespaces = self.getContainingNamespaces(self.sourceObject, [])
        if namespaces:
            output = body
            for ns in namespaces:
                output = "namespace {} {{\n{}\n}}".format(ns, output)
            return output
        else:
            return body

    def __str__(self):
        className = self.sourceObject.spelling
        namespaces = self.getContainingNamespaces(self.sourceObject, [])
        for ns in namespaces:
            className = "{}::{}".format(ns, className)
        return className