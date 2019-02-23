/*//////////////////////////////////////////////////////////////////////////////

Copyright(c) 2014, Thomas Senfter
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and / or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/*//////////////////////////////////////////////////////////////////////////////

#ifndef __MY_FILEIO_BASE_H__
#define __MY_FILEIO_BASE_H__

#include <wx/fileconf.h>
#include <wx/wfstream.h>
#include <pugixml.hpp>
#include <vector>
#include <queue>
#include <sstream>

namespace MY{
  enum MultiValueElementIndexing{     //default indexing of values written in one write call
    INDEX_WITH_NUMBERS_FROM_0, INDEX_WITH_NUMBERS_FROM_1, INDEX_WITH_LETTERS_FROM_a,
    INDEX_WITH_x_y_z_w, INDEX_WITH_u_v, INDEX_WITH_r_g_b_a
  };

  enum SettingFileError{
    FILE_ERROR_NONE, FILE_ERROR_FILE_NOT_FOUND, FILE_ERROR_IO_ERROR, FILE_ERROR_SAVING_ERROR, FILE_ERROR_NO_MEMORY, FILE_ERROR_PARSING_ERROR,
    FILE_ERROR_NOT_READY, FILE_ERROR_ATTR_MISSING, FILE_ERROR_NODE_MISSING, FILE_ERROR_WRONG_TYPE, FILE_ERROR_NOT_ENOUGH_ATTR_NAMES,
    FILE_ERROR_WRITING_ERROR
  };

  enum SettingFileWarning{ FILE_WARNING_NONE, FILE_WARNING_OVERWRITE_ATTR };

  //generate attribute names with name and indexing style
  std::queue<std::string> getIndexedAttrNames(const std::string& attr_name, unsigned number,
    MultiValueElementIndexing indexing_mode = INDEX_WITH_NUMBERS_FROM_0);


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  //class for a setting item (has value, a name and nodes(for XML)
  template<typename T> class Setting{
  private:
    T value_;
    std::string name_;
    std::vector<std::string> nodes_;

  public:
    //default value for nodes is no nodes (as needed in INI)
    Setting(const std::string& name, const std::vector<std::string>& nodes = std::vector<std::string>())
      : name_(name), nodes_(nodes){}
    Setting(const std::string& name, const T& value, const std::vector<std::string>& nodes = std::vector<std::string>())
      : name_(name), value_(value), nodes_(nodes){}

    //for implicit casting to value type
    operator T&() { return value_; }
    operator const T&() const { return value_; }
    T& operator=(const T& value){     //assigment to value
      value_ = value;
      return *this;
    }
    T* operator->(){ return &value_; }      //getting value

    const T& getValue() const { return value_; }
    void setValue(const T& value){ value_ = value; }
    const std::string& getName() const { return name_; }
    void setName(const std::string& name){ name_ = name; }
    const std::vector<std::string>& getNodes() const { return nodes_; }
    void setNodes(std::vector<std::string>& nodes){ nodes_ = nodes; }
  };


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //base class for setting file
  class SettingFile_Base{
  protected:
    std::string filename_ = "";
    bool is_ready_ = false;
    std::queue<SettingFileError> errors_;
    std::queue<SettingFileWarning> warnings_;

  public:
    SettingFile_Base(const std::string& filename) : filename_(filename){};
    virtual ~SettingFile_Base(){};

    bool isReady() const { return is_ready_; }
    bool isError() const { return !!errors_.size(); }
    SettingFileError getError() const;     //just returning error
    bool isWarning() const { return !!warnings_.size(); }
    SettingFileWarning getWarning() const { return warnings_.front(); }
    const std::string& getFilename() const { return filename_; }

    SettingFileError popError();      //returns error and pops it from queue
    SettingFileWarning popWarning();
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //base class for Input files (XML, INI and maybe more someday)
  class SettingFileIn_Base : public SettingFile_Base{
  protected:
    virtual bool load(const std::string& filename) = 0;

  public:
    SettingFileIn_Base(const std::string& filename) : SettingFile_Base(filename){};
    virtual ~SettingFileIn_Base(){};

    //getting a value of the given type
    virtual bool getValue(std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool getValue(wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool getValue(bool& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool getValue(int& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool getValue(float& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool getValue(double& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;

    //template for other types ( << operator of type needed)
    template<typename T> bool getValue(T& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    template<typename T> bool getValue(Setting<T>& value);

    //get many values with one call (variadic template for different types)
    template<typename T1, typename... T2> bool getValues(
      std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
      T1& first_value, T2& ... other_values);

    //same as getValue template, but needed for variadic template (as end)
    template<typename T> bool getValues(
      std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
      T& value);
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //class for Ini-files, implemented with wxFileConfig
  class IniFileIn : public SettingFileIn_Base{
  protected:
    wxFileInputStream* file_stream = nullptr;
    wxFileConfig* file = nullptr;

    virtual bool load(const std::string& filename);

  public:
    IniFileIn(const std::string& filename);   //construct ini file class with filename for a file
    ~IniFileIn();

    virtual bool getValue(std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(bool& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(int& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(float& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(double& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);

    template<typename T1, typename... T2> bool getValues(
      std::queue<std::string> attr_names, T1& first_value, T2& ... other_values);
    template<typename T> bool getValues(std::queue<std::string> attr_names, T& value);

    using SettingFileIn_Base::getValue;
    using SettingFileIn_Base::getValues;
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //class for XML-files, implemented with pugixml
  class XmlFileIn : public SettingFileIn_Base{
  protected:
    pugi::xml_document* doc = nullptr;

    pugi::xml_attribute findAttribute(const std::string& attr_name, const std::vector<std::string>* const nodes);
    virtual bool load(const std::string& filename);

  public:
    XmlFileIn(const std::string& filename);   //construct ini file class with filename for a file
    ~XmlFileIn();

    virtual bool getValue(std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(bool& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(int& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(float& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool getValue(double& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);

    using SettingFileIn_Base::getValue;
    using SettingFileIn_Base::getValues;
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //base class for output files
  class SettingFileOut_Base : public SettingFile_Base{
  protected:

  public:
    SettingFileOut_Base(const std::string& filename) : SettingFile_Base(filename){};
    virtual ~SettingFileOut_Base(){};

    virtual bool save(const std::string& filename = std::string()) = 0;

    virtual bool setValue(const std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool setValue(const wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool setValue(bool value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool setValue(int value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool setValue(float value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;
    virtual bool setValue(double value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr) = 0;

    template<typename T> bool setValue(const T& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    template<typename T> bool setValue(const Setting<T>& value);

    template<typename T1, typename... T2> bool setValues(
      std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
      const T1& first_value, const T2& ... other_values);

    template<typename T> bool setValues(
      std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
      const T& value);
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //class for ini-files, implemented with wxFileConfig
  class IniFileOut : public SettingFileOut_Base{
  protected:
    wxFileConfig* file = nullptr;

  public:
    IniFileOut(const std::string& filename);
    ~IniFileOut();

    virtual bool save(const std::string& filename = "");

    virtual bool setValue(const std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(const wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(bool value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(int value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(float value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(double value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);

    template<typename T1, typename... T2> bool setValues(
      std::queue<std::string> attr_names, const T1& first_value, const T2& ... other_values);
    template<typename T> bool setValues(std::queue<std::string> attr_names, const T& value);

    using SettingFileOut_Base::setValue;
    using SettingFileOut_Base::setValues;
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //class for XML-files, , implemented with wxFileConfig
  class XmlFileOut : public SettingFileOut_Base{
  protected:
    pugi::xml_document* doc = nullptr;

    pugi::xml_attribute getWriteAttribute(const std::string& attr_name, const std::vector<std::string>* const nodes);

  public:
    XmlFileOut(const std::string& filename);
    ~XmlFileOut();

    virtual bool save(const std::string& filename = "");

    virtual bool setValue(const std::string& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(const wxString& value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(bool value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(int value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(float value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);
    virtual bool setValue(double value, const std::string& attr_name,
      const std::vector<std::string>* const nodes = nullptr);

    using SettingFileOut_Base::setValue;
  };

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  template<typename T> bool SettingFileIn_Base::getValue(T& value, const std::string& attr_name,
    const std::vector<std::string>* const nodes)
  {
    //saved as a string, get the string and parse it
    std::stringstream stream;
    std::string value_string;
    if (!getValue(value_string, attr_name, nodes))
      return false;
    stream << value_string;
    stream >> value;
    return true;
  }

  template<typename T> bool SettingFileIn_Base::getValue(Setting<T>& value){
    return getValue(static_cast<T&>(value), value.getName(), &(value.getNodes()));
  }


  template<typename T1, typename... T2> bool SettingFileIn_Base::getValues(
    std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
    T1& first_value, T2& ... other_values)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    if (!getValue(first_value, attr_names.front(), nodes))
      return false;
    attr_names.pop();
    getValues(attr_names, nodes, other_values...);

    return true;
  }

  template<typename T1, typename... T2> bool IniFileIn::getValues(
    std::queue<std::string> attr_names, T1& first_value, T2& ... other_values)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    if (!getValue(first_value, attr_names.front()))
      return false;
    attr_names.pop();
    getValues(attr_names, other_values...);

    return true;
  }

  template<typename T> bool SettingFileIn_Base::getValues(
    std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
    T& value)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    return getValue(value, attr_names.front(), nodes);
  }

  template<typename T> bool IniFileIn::getValues(std::queue<std::string> attr_names, T& value){
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    return getValue(value, attr_names.front());
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  template<typename T> bool SettingFileOut_Base::setValue(const T& value, const std::string& attr_name,
    const std::vector<std::string>* const nodes)
  {
    std::stringstream stream;
    stream << value;
    return setValue(stream.str(), attr_name, nodes);
  }

  template<typename T> bool SettingFileOut_Base::setValue(const Setting<T>& value){
    return setValue(value.getValue(), value.getName(), &(value.getNodes()));
  }


  template<typename T1, typename... T2> bool SettingFileOut_Base::setValues(
    std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
    const T1& first_value, const T2& ... other_values)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    if (!setValue(first_value, attr_names.front(), nodes))
      return false;
    attr_names.pop();
    setValues(attr_names, nodes, other_values...);

    return true;
  }

  template<typename T1, typename... T2> bool IniFileOut::setValues(
    std::queue<std::string> attr_names, const T1& first_value, const T2& ... other_values)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    if (!setValue(first_value, attr_names.front()))
      return false;
    attr_names.pop();
    setValues(attr_names, other_values...);

    return true;
  }

  template<typename T> bool SettingFileOut_Base::setValues(
    std::queue<std::string> attr_names, const std::vector<std::string>* const nodes,
    const T& value)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    return setValue(value, attr_names.front(), nodes);
  }

  template<typename T> bool IniFileOut::setValues(std::queue<std::string> attr_names, const T& value){
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!attr_names.size()){
      errors_.push(FILE_ERROR_NOT_ENOUGH_ATTR_NAMES);
      return false;
    }
    return setValue(value, attr_names.front());
  }


}


#endif //__MY_FILEIO_BASE_H__
