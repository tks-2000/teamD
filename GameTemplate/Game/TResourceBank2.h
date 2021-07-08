#pragma once
template<class TResource2>
class TResourceBank2
{
public:
	TResource2* Get(const char* filePath)
	{
		auto it = m_resourceMap.find(filePath);
		if (it != m_resourceMap.end()) {
			//ÉoÉìÉNÇ…ìoò^Ç≥ÇÍÇƒÇ¢ÇÈÅB
			return it->second.get();
		}
		return nullptr;
	}
	void Regist(const char* filePath, TResource2* resource)
	{
		auto it = m_resourceMap.find(filePath);
		if (it == m_resourceMap.end()) {
			//ñ¢ìoò^ÅB
			m_resourceMap.insert(
				std::pair< std::string, TResource2Ptr>(filePath, resource)
			);
		}
	}
private:
	using TResource2Ptr = std::unique_ptr<TResource2>;
	std::map<std::string, TResource2Ptr> m_resourceMap;
};

