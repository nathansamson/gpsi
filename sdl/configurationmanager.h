#ifndef INC_CONFIGURATION_H
#define INC_CONFIGURATION_H

#include "tinyxml/ticpp.h"

namespace SISDL {
	/**
	 * A configuration manager
	*/
	class ConfigurationManager {
	public:
		/**
		 * Returns the value of a boolean option
		 *
		 * @param option The name of the option.
		 * @return The value of the option.
		*/
		static bool getOption(std::string option) {
			 return get().getInternalOption(option);
		}
	
		/**
		 * Returns the value of an option
		 *
		 * @param option The name of the option.
		 * @return The value of the option.
		*/
		template<typename T>
		static T getOption(std::string option) {
			 return get().getInternalOption<T>(option);
		}
	
		/**
		 * Set the value of an option
		 *
		 * @param name The name of the option.
		 * @param value The value of the option.
		*/
		template<typename T>
		static void setOption(std::string name, T value) {
			get().setInternalOption(name, value);
		}
		
		/**
		 * Set the value of a boolean option
		 *
		 * @param name The name of the option.
		 * @param value The value of the option.
		*/
		static void setOption(std::string name, bool value) {
			get().setInternalOption(name, value);
		}
	private:
		/**
		 * Returns the location of the config file.
		 *
		 * @return The location of the config file.
		*/
		static std::string getConfigFile() {
			char* pFilePath = getenv("XDG_CONFIG_HOME");
			std::string fileName = "gpsi.conf";
			std::string filePath;
			if (pFilePath == 0) {
				pFilePath = getenv("HOME");
				if (pFilePath == 0) {
					pFilePath = getenv("USERPROFILE");
					if (pFilePath == 0) {
						fileName = ".gpsi.conf";
						filePath = "."; // Current Working directory...
					} else {
						filePath = pFilePath;
						filePath += "/.config";
					}
				} else {
					filePath = pFilePath;
					filePath += "/.config";
				}
			} else {
				filePath = pFilePath;
			}
			return filePath + "/" + fileName;
		}
	
		/**
		 * Get instance of the config manager.
		 *
		 * @return A uniuqe instance of the config manager.
		*/
		static ConfigurationManager& get() {
			static ConfigurationManager config = ConfigurationManager(getConfigFile());
			return config;
		}
	
		/**
		 * Returns the value of an option
		 *
		 * @param option The name of the option.
		 * @return The value of the option.
		*/
		template<typename T>
		T getInternalOption(std::string name) {
			T val;
			try {
				fDocument.FirstChildElement("configuration")->FirstChildElement(name)->GetText(&val);
			} catch (...) {
			}
			return val;
		}
		
		/**
		 * Returns the value of a boolean option
		 *
		 * @param option The name of the option.
		 * @return The value of the option.
		*/
		bool getInternalOption(std::string name) {
			try {
				std::string text = fDocument.FirstChildElement("configuration")->FirstChildElement(name)->GetText();
				if (text == "true") {
					return true;
				} else {
					return false;
				}
			} catch (...) {
				return false;	
			}
		}
		
		/**
		 * Set the value of an option
		 *
		 * @param name The name of the option.
		 * @param value The value of the option.
		*/
		template<typename T>
		void setInternalOption(std::string name, T val) {
			ticpp::Element* config = fDocument.FirstChildElement("configuration")->FirstChildElement(name, false);
			if (config == 0) {
				config = new ticpp::Element(name);
				config->SetText(val);
				fDocument.FirstChildElement("configuration")->LinkEndChild(config);
			} else {
				config->SetText(val);
			}
		}
		
		/**
		 * Set the value of a boolean option
		 *
		 * @param name The name of the option.
		 * @param value The value of the option.
		*/
		void setInternalOption(std::string name, bool val) {
			ticpp::Element* config = fDocument.FirstChildElement("configuration")->FirstChildElement(name, false);
			if (config == 0) {
				config = new ticpp::Element(name);
				if (val) {
					config->SetText("true");
				} else {
					config->SetText("false");
				}
				fDocument.FirstChildElement("configuration")->LinkEndChild(config);
			} else {
				if (val) {
					config->SetText("true");
				} else {
					config->SetText("false");
				}
			}
		}
	
		ConfigurationManager();
		/**
		 * Constructor.
		 *
		 * @param file The filename of the configuration file.
		*/
		ConfigurationManager(std::string file): fDocument(file) {
			ticpp::Element* root;
			try {
				fDocument.LoadFile();
				root = fDocument.FirstChildElement("configuration");
			} catch (...) {
				root = new ticpp::Element("configuration");
				fDocument.LinkEndChild(root);
			}
		}
		
		~ConfigurationManager() {
			fDocument.SaveFile();
		}
		
		/**
		 * The XML document of the config file.
		*/
		ticpp::Document fDocument;
	};
}

#endif // INC_CONFIGURATION_H
