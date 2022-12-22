#ifndef DF33D42B_C736_4AD0_9BB2_C1F1261E31D7
#define DF33D42B_C736_4AD0_9BB2_C1F1261E31D7

#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>
#include <boost/dll/import_class.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/shared_library.hpp>
#include <memory>

template <class ClassBase>
std::shared_ptr<ClassBase> ClassLoader::createSharedInstance(const std::string& symbolName,
                                                             const std::string& libraryName,
                                                             const std::string& libraryDirectory) {}

#endif /* DF33D42B_C736_4AD0_9BB2_C1F1261E31D7 */
