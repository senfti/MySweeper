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

#include "My_SettingFile.h"
#include <iomanip>

namespace MY{

  std::queue<std::string> getIndexedAttrNames(const std::string& attr_name, unsigned number, MultiValueElementIndexing indexing_mode){
    std::queue<std::string> attr_names;
    for (unsigned i = 0; i < number; i++){
      switch (indexing_mode)
      {
      case MY::INDEX_WITH_NUMBERS_FROM_0:
        attr_names.push(attr_name + "_" + std::to_string(i));
        break;
      case MY::INDEX_WITH_NUMBERS_FROM_1:
        attr_names.push(attr_name + "_" + std::to_string(i + 1));
        break;
      case MY::INDEX_WITH_LETTERS_FROM_a:
        attr_names.push(attr_name + "_" + static_cast<char>('a' + i)); //starting with 'a'
        break;
      case MY::INDEX_WITH_x_y_z_w:                                    //starting with 'x', you should use it with 2 <= number <= 4
        if (i < 3)
          attr_names.push(attr_name + "_" + static_cast<char>('x' + i));
        else
          attr_names.push(attr_name + "_" + static_cast<char>('w')); //if i==3 -> w
        break;
      case MY::INDEX_WITH_u_v:                                    //starting with 'u', you should use it with number == 2
        attr_names.push(attr_name + "_" + static_cast<char>('u' + i));
        break;
      case MY::INDEX_WITH_r_g_b_a:
        switch (i){
        case 0: attr_names.push(attr_name + "_" + static_cast<char>('r')); break;
        case 1: attr_names.push(attr_name + "_" + static_cast<char>('g')); break;
        case 2: attr_names.push(attr_name + "_" + static_cast<char>('b')); break;
        case 3: attr_names.push(attr_name + "_" + static_cast<char>('a')); break;
        }
        break;
      default:
        attr_names.push(attr_name);
        break;
      }
    }
    return attr_names;
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  SettingFileError SettingFile_Base::getError() const {
    if (errors_.empty())
      return FILE_ERROR_NONE;
    return errors_.front(); 
  }

  SettingFileError SettingFile_Base::popError(){
    if (errors_.empty())
      return FILE_ERROR_NONE;

    SettingFileError error = errors_.front();
    errors_.pop();
    return error;
  }

  SettingFileWarning SettingFile_Base::popWarning(){
    if (warnings_.empty())
      return FILE_WARNING_NONE;

    SettingFileWarning warning = warnings_.front();
    warnings_.pop();
    return warning;
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  IniFileIn::IniFileIn(const std::string& filename) : SettingFileIn_Base(filename){
    load(filename);
  }

  IniFileIn::~IniFileIn(){
    delete file;
    delete file_stream;
  }

  bool IniFileIn::load(const std::string& filename){
    delete file;
    file = nullptr;
    delete file_stream;
    file_stream = nullptr;

    try{
      file_stream = new wxFileInputStream(filename);
    }
    catch (std::bad_alloc&){
      errors_.push(FILE_ERROR_NO_MEMORY);
      file_stream = nullptr;
      return false;
    }
    if (!file_stream->Ok()){
      errors_.push(FILE_ERROR_FILE_NOT_FOUND);
      delete file_stream;
      file_stream = nullptr;
      return false;
    }

    try{
      file = new wxFileConfig(*file_stream);
    }
    catch (std::bad_alloc&){
      errors_.push(FILE_ERROR_NO_MEMORY);
      file = nullptr;
      delete file_stream;
      file_stream = nullptr;
      return false;
    }

    is_ready_ = true;
    return true;
  }

  bool IniFileIn::getValue(std::string& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    wxString temp;
    if (!file->Read(attr_name, &temp)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    value = temp;
    return true;
  }

  bool IniFileIn::getValue(wxString& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!file->Read(attr_name, &value)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    return true;
  }

  bool IniFileIn::getValue(bool& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!file->Read(attr_name, &value)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    return true;
  }

  bool IniFileIn::getValue(int& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!file->Read(attr_name, &value)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    return true;
  }

  bool IniFileIn::getValue(float& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!file->Read(attr_name, &value)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    return true;
  }

  bool IniFileIn::getValue(double& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    if (!file->Read(attr_name, &value)){
      errors_.push(FILE_ERROR_ATTR_MISSING);
      return false;
    }
    return true;
  }


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  XmlFileIn::XmlFileIn(const std::string& filename) : SettingFileIn_Base(filename){
    load(filename);
  }

  XmlFileIn::~XmlFileIn(){
    delete doc;
  }

  bool XmlFileIn::load(const std::string& filename){
    delete doc;
    doc = nullptr;

    try{
      doc = new pugi::xml_document;
    }
    catch (std::bad_alloc&){
      errors_.push(FILE_ERROR_NO_MEMORY);
      doc = nullptr;
      return false;
    }

    switch (doc->load_file(filename.c_str()).status){
    case pugi::status_ok:               is_ready_ = true;                             return true;
    case pugi::status_file_not_found:   errors_.push(FILE_ERROR_FILE_NOT_FOUND);      return false;
    case pugi::status_io_error:         errors_.push(FILE_ERROR_IO_ERROR);            return false;
    case pugi::status_out_of_memory:    errors_.push(FILE_ERROR_NO_MEMORY);           return false;
    default:                            errors_.push(FILE_ERROR_PARSING_ERROR);       return false;
    }
  }

  pugi::xml_attribute XmlFileIn::findAttribute(const std::string& attr_name, const std::vector<std::string>* nodes){
    pugi::xml_node node = *doc;
    if (nodes){
      for (unsigned i = 0; i < nodes->size(); i++){
        node = node.child((*nodes)[i].c_str());
        if (node.type() == pugi::node_null){
          errors_.push(FILE_ERROR_NODE_MISSING);
          return pugi::xml_attribute();
        }
      }
    }
    pugi::xml_attribute attr = node.attribute(attr_name.c_str());
    if (!attr)
      errors_.push(FILE_ERROR_ATTR_MISSING);
    return attr;
  }

  bool XmlFileIn::getValue(std::string& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = static_cast<const char*>(attr.as_string());
    return true;
  }

  bool XmlFileIn::getValue(wxString& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = static_cast<const char*>(attr.as_string());
    return true;
  }

  bool XmlFileIn::getValue(bool& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = attr.as_bool();
    return true;
  }

  bool XmlFileIn::getValue(int& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = attr.as_int();
    return true;
  }

  bool XmlFileIn::getValue(float& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = attr.as_float();
    return true;
  }

  bool XmlFileIn::getValue(double& value,
    const std::string& attr_name, const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    pugi::xml_attribute attr = findAttribute(attr_name, nodes);
    if (!attr)
      return false;
    value = attr.as_double();
    return true;
  }


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  IniFileOut::IniFileOut(const std::string& filename) : SettingFileOut_Base(filename){
    try{
      file = new wxFileConfig();
    }
    catch (std::bad_alloc&){
      errors_.push(FILE_ERROR_NO_MEMORY);
      file = nullptr;
    }
    is_ready_ = true;
  }

  IniFileOut::~IniFileOut(){
    delete file;
  }

  bool IniFileOut::save(const std::string& filename){
    if (!filename.empty())
      filename_ = filename;

    wxFileOutputStream file_stream(filename_);
    if (!file_stream.Ok()){
      errors_.push(FILE_ERROR_IO_ERROR);
      return false;
    }

    if (!file->Save(file_stream)){
      errors_.push(FILE_ERROR_SAVING_ERROR);
      return false;
    }

    return true;
  }

  bool IniFileOut::setValue(const std::string& value, const std::string& attr_name,
    const std::vector<std::string>* nodes){
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    return file->Write(attr_name, wxString(value));
  }

  bool IniFileOut::setValue(const wxString& value, const std::string& attr_name,
    const std::vector<std::string>* nodes){
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    return file->Write(attr_name, value);
  }

  bool IniFileOut::setValue(bool value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    return file->Write(attr_name, value);
  }

  bool IniFileOut::setValue(int value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    return file->Write(attr_name, value);
  }

  bool IniFileOut::setValue(float value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    wxString out = wxString::Format("%.8e", value);
    return file->Write(attr_name, out);
  }

  bool IniFileOut::setValue(double value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }
    wxString out = wxString::Format("%.17e", value);
    return file->Write(attr_name, out);
  }


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  XmlFileOut::XmlFileOut(const std::string& filename) : SettingFileOut_Base(filename){
    try{
      doc = new pugi::xml_document();
    }
    catch (std::bad_alloc&){
      errors_.push(FILE_ERROR_NO_MEMORY);
      doc = nullptr;
    }
    is_ready_ = true;
  }

  XmlFileOut::~XmlFileOut(){
    delete doc;
  }

  bool XmlFileOut::save(const std::string& filename){
    if (!filename.empty())
      filename_ = filename;

    if (!doc->save_file(filename_.c_str())){
      errors_.push(FILE_ERROR_SAVING_ERROR);
      return false;
    }

    return true;
  }

  pugi::xml_attribute XmlFileOut::getWriteAttribute(const std::string& attr_name, const std::vector<std::string>* nodes){
    pugi::xml_node write_node = *doc;
    pugi::xml_node temp_node;
    pugi::xml_attribute write_attr;

    if (!nodes){
      write_node = doc->child("Default_Node");
      if (write_node.type() == pugi::node_null)
        write_node = doc->append_child("Default_Node");
    }
    else{
      for (unsigned i = 0; i < nodes->size(); i++){
        temp_node = write_node;
        write_node = write_node.child((*nodes)[i].c_str());
        if (write_node.type() == pugi::node_null){
          write_node = temp_node.append_child((*nodes)[i].c_str());
        }
      }
    }

    write_attr = write_node.attribute(attr_name.c_str());
    if (write_attr)
      warnings_.push(FILE_WARNING_OVERWRITE_ATTR);
    else
      write_attr = write_node.append_attribute(attr_name.c_str());

    if (!write_attr)
      errors_.push(FILE_ERROR_WRITING_ERROR);
    return write_attr;
  }

  bool XmlFileOut::setValue(const std::string& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    if (!write_attr.set_value(value.c_str())){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }

  bool XmlFileOut::setValue(const wxString& value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    if (!write_attr.set_value(value.mb_str())){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }

  bool XmlFileOut::setValue(bool value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    if (!write_attr.set_value(value)){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }

  bool XmlFileOut::setValue(int value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    if (!write_attr.set_value(value)){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }

  bool XmlFileOut::setValue(float value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    std::ostringstream out;
    out << std::setprecision(8) << value;

    if (!write_attr.set_value(out.str().c_str())){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }

  bool XmlFileOut::setValue(double value, const std::string& attr_name,
    const std::vector<std::string>* nodes)
  {
    if (!is_ready_){
      errors_.push(FILE_ERROR_NOT_READY);
      return false;
    }

    pugi::xml_attribute write_attr = getWriteAttribute(attr_name, nodes);
    if (!write_attr)
      return false;

    std::ostringstream out;
    out << std::setprecision(17) << value;

    if (!write_attr.set_value(out.str().c_str())){
      errors_.push(FILE_ERROR_WRITING_ERROR);
      return false;
    }
    return true;
  }
}
