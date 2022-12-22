#ifndef CDC614B3_431B_4382_83CA_44CD2CA88CB6
#define CDC614B3_431B_4382_83CA_44CD2CA88CB6
#ifndef DF33D42B_C736_4AD0_9BB2_C1F1261E31D7
#define DF33D42B_C736_4AD0_9BB2_C1F1261E31D7

#include <memory>
#include <string>
#include <vector>

struct ClassLoader {
  template <class ClassBase>
  std::shared_ptr<ClassBase> ClassLoader::createSharedInstance(const std::string& symbolName,
                                                               const std::string& libraryName,
                                                               const std::string& libraryDirectory = "");

  static inline bool isClassAvailable(const std::string& symbolName, const std::string& libraryName,
                                      const std::string& libraryDirectory = "");

  static inline std::vector<std::string> getAvailableSymbols(const std::string& section, const std::string& libraryName,
                                                             const std::string& libraryDirectory = "");
}

#endif /* DF33D42B_C736_4AD0_9BB2_C1F1261E31D7 */

#endif /* CDC614B3_431B_4382_83CA_44CD2CA88CB6 */
