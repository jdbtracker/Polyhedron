from .CxxNode import CxxNode

class CxxClass(CxxNode):
    
    def __init__(self, sourceObject, parent = None):
        CxxNode.__init__(self, sourceObject, parent)

    def get_inheritance_hierarchy(self):
        pass
    # def function

    def __str__(self):
        className = self.sourceObject.spelling
        namespaces = self.getContainingNamespaces(self.sourceObject, [])
        for ns in namespaces:
            className = "{}::{}".format(ns, className)
        return className