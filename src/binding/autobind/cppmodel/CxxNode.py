from clang import cindex

class CxxNode():
    
    def __init__(self, sourceObject, parent = None):
        # self.cxxtype = cxxtype
        self.sourceObject = sourceObject
        self.parent = parent
        self.children = []

        if not self.parent is None:
            self.parent.addchild(self)

        pass

    def addchild(self, node):
        node.parent = self
        if node not in self.children:
            self.children.append(node)
        pass

    def delchild(self, node):
        if node in self.children:
            self.children.remove(node)
            node.parent = None
        pass
    
    def forEachChild(self, depthFirst = False):
        for child in self.children:
            if depthFirst:
                yield from child.forEachChild(depthFirst)
            yield child
            if not depthFirst:
                yield from child.forEachChild(depthFirst)

    def dump(self, level = 0):
        pretext = " |" * level
        output = pretext + " +"+ self.__class__.__qualname__  + " " + str(self) + "\n"
        for child in self.children:
            output += child.dump(level + 1)

        return output


    def getContainingNamespaces(self, node, data):
        if node is None:
            data = self.getContainingNamespaces(self.sourceObject, data)
        else:
            if node:
                if (node.kind == cindex.CursorKind.NAMESPACE):
                    data.append(node.spelling)
                if node.semantic_parent and node.semantic_parent.kind != cindex.CursorKind.TRANSLATION_UNIT:
                    data = self.getContainingNamespaces(node.semantic_parent, data)
        return data

    def __str__(self):
        return self.sourceObject.spelling