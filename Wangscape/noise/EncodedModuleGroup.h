#pragma once

#include <map>
#include <string>
#include <iostream>

#include <spotify/json.hpp>

#include "noise/module/ModulePtr.h"
#include "noise/module/ModuleWithSources.h"
#include "module/codecs/NoiseSourcesCodec.h"
#include "module/codecs/ModuleCodecs.h"

#include "ModuleID.h"

namespace noise
{

class ModuleGroup;

class EncodedModuleGroup
{
public:
    EncodedModuleGroup();
    typedef spotify::json::encoded_value_ref EncodedValueRef;
    typedef std::map<ModuleID, EncodedValueRef> EncodedModuleMap;

    EncodedModuleMap encodedModules;
    std::shared_ptr<ModuleGroup> moduleGroup;

    void decode();
    
private:

    template<typename T>
    static T extractValue(const EncodedValueRef& source, const std::string& key);

    template<typename M>
    static module::ModuleWithSources decodeModule(const EncodedValueRef& source);

    typedef std::function<module::ModuleWithSources(const EncodedValueRef&)> ModuleDecodeFn;
    typedef std::map<std::string, ModuleDecodeFn> ModuleDecodeTable;
    
    static ModuleDecodeTable mModuleDecodeTable;
};

template<typename T>
inline T EncodedModuleGroup::extractValue(const EncodedValueRef& source, const std::string& key)
{
    auto codec = spotify::json::codec::map<EncodedModuleMap, spotify::json::codec::any_value_t>(spotify::json::codec::any_value());
    std::map<std::string, spotify::json::encoded_value_ref> partial_decode = spotify::json::decode(codec, source.data(), source.size());
    const EncodedValueRef& value = partial_decode.at(key);
    return spotify::json::decode<T>(value.data(), value.size());
}

template<typename M>
inline module::ModuleWithSources EncodedModuleGroup::decodeModule(const EncodedValueRef& source)
{
    module::ModuleWithSources result;
    std::shared_ptr<module::Wrapper<M>> module_p = spotify::json::decode<std::shared_ptr<module::Wrapper<M>>>(source.data(), source.size());
    result.module = module_p;
    result.noiseSources = spotify::json::decode<module::NoiseSources>(source.data(), source.size());
    return result;
}

} // namespace noise