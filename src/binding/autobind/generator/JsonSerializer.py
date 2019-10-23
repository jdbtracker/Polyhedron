
def Generate(cxxRootNode):
    from ..cppmodel.CxxClass import CxxClass
    
    template = """#include "shared/entities/coreentity.h"
{}"""
    generated_funcs = []
    for node in cxxRootNode.forEachChild():
        if type(node) is CxxClass:
            generated_funcs.append(GenerateFromJson(node))
            generated_funcs.append(GenerateToJson(node))
            generated_funcs.append(GenerateJsonDebug(node))
    if len(generated_funcs) == 0:
        return ""
    return template.format("\n".join(generated_funcs))

def GenerateJsonVariableTemplateValues(cxxVar):
    variableName = cxxVar.sourceObject.spelling
    variableType = cxxVar.sourceObject.type.spelling

    return {
        "variableName": variableName,
        "variableType": variableType
    }

def GenerateJsonTemplateValues(cxxClass):
    className = str(cxxClass)

    return {
        "className": className
    }

def GenerateFromJson(cxxClass):
    return ""

def GenerateToJson(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)

    output = []
    for child in cxxClass.forEachChild():
        output = output + GenerateToJsonVariable(child)
    body = ",\n\t\t".join(output)
    return f"""nlohmann::json {templateValues['className']}::toJson()
{{
\treturn {{
\t\t{body}
\t}};
}}
"""

def GenerateToJsonVariable(cxxVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    if (templateValues["variableType"] == "vec"):
        output_obj = []
        for m in ['x', 'y', 'z']:
            output_obj.append(f"\t\"{m}\": {templateValues['variableName']}.{m}")
        output = [f"{{\"{templateValues['variableName']}\""] + output_obj + ["}"]
    else:
        output.append(f"\"{templateValues['variableName']}\", {templateValues['variableName']}")
    return output


def GenerateJsonDebug(cxxClass):
    debug_output = []
    for child in cxxClass.forEachChild():
        debug_output.append(GenerateJsonVariableDebug(child))
    
    return "\n".join(debug_output)

def GenerateJsonVariableDebug(cxxVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)

    output = []
    for key in templateValues:
        output.append(f"// {key} => {templateValues[key]}")
    return "\n".join(output)