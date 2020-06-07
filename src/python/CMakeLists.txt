find_package(pybind11 CONFIG REQUIRED)

set(module_name bn_crypto)

add_library(${module_name} MODULE ${module_name}.cpp)
target_link_libraries(${module_name} PRIVATE pybind11::module)
target_link_libraries(${module_name} PRIVATE bluenebula-crypto)
set_target_properties(${module_name} PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
target_compile_definitions(${module_name} PRIVATE -DMODULE_NAME=${module_name})
