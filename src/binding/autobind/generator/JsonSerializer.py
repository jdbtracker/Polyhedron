CUSTOM_TOJSON_VARGENERATORS = {}
CUSTOM_FROMJSON_VARGENERATORS = {}

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

    if templateValues["variableType"] in CUSTOM_TOJSON_VARGENERATORS:
        output = output + CUSTOM_TOJSON_VARGENERATORS[templateValues["variableType"]](templateValues)
    else:
        output.append(f"\"{templateValues['variableName']}\", {templateValues['variableName']}")
    return output


def GenerateFromJson(cxxClass):
    templateValues = GenerateJsonTemplateValues(cxxClass)

    output = []
    for child in cxxClass.forEachChild():
        output = output + GenerateFromJsonVariable(child)
    body = "\n\t".join(output)
    return f"""void {templateValues['className']}::fromJson(const nlohmann::json& document)
{{
\t{body}
}}
"""

def GenerateFromJsonVariable(cxxVar):
    templateValues = GenerateJsonVariableTemplateValues(cxxVar)
    output = []

    if templateValues["variableType"] in CUSTOM_FROMJSON_VARGENERATORS:
        output = output + CUSTOM_FROMJSON_VARGENERATORS[templateValues["variableType"]](templateValues)
    else:
        output.append(f"json_utils::tryQueryJsonVar(document, \"{templateValues['variableName']}\", {templateValues['variableName']});")
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

# ---- Custom Generators for specific variable types

def CustomVarGenerator_toJson_vec(templateValues):
    output_obj = []
    for m in ['x', 'y', 'z']:
        output_obj.append(f"\t\"{m}\": {templateValues['variableName']}.{m}")
    return [f"{{\"{templateValues['variableName']}\""] + output_obj + ["}"]

CUSTOM_TOJSON_VARGENERATORS['vec'] = CustomVarGenerator_toJson_vec