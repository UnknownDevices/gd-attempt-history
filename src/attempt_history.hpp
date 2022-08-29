#pragma once

#include <attempt.hpp>
#include <fbs/attempt_history.fbs.h>

namespace gd_att_history {
  struct AttemptHistory final : public std::vector<Attempt> {
  public:
    i32 level_id; 

    std::wstring mod_local_app_data_path() {
      PWSTR local_app_data_path;
      SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &local_app_data_path);
      auto output = std::wstring(local_app_data_path);
      CoTaskMemFree(local_app_data_path);

      std::replace(output.begin(), output.end() - 1, L'\\', L'/');
      output += L"/GeometryDash/GDAH";
      return output;
    }

    void register_att(Attempt const& att) {
      push_back(att);
      att.debug();
    }

    void save() {
      flatbuffers::FlatBufferBuilder builder(64);

      std::vector<flatbuffers::Offset<fbs::Attempt>> fbs_atts;
      fbs_atts.reserve(size());
      for (auto att : *this) {
        fbs_atts.push_back(fbs::CreateAttempt(builder,
          att.start_time, att.start_perc, att.end_perc, static_cast<u8>(att.flags)));
      }

      auto fbs_att_history = fbs::CreateAttemptHistory(
        builder, builder.CreateVector(fbs_atts));
      builder.Finish(fbs_att_history);

      auto file_path = mod_local_app_data_path() + std::format(L"/{}.dat", level_id);
      auto size = builder.GetSize();
      auto buf = builder.GetBufferPointer();

      auto f = std::fstream(file_path, std::ios::binary | std::ios::out);
      if (f.is_open()) {
        f.write(reinterpret_cast<char*>(buf), size);
        f.close();
      }
      else {
        return;
      }

      debug();
    }

    void load() {
      using namespace std::filesystem;

      auto file_path = mod_local_app_data_path() + std::format(L"/{}.dat", level_id);
      if (!directory_entry(path(file_path)).exists()) {
        return;
      }

      auto size = static_cast<u32>(file_size(path(file_path)));
      auto buf = new char[size];
      
      auto f = std::fstream(file_path, std::ios::binary | std::ios::in);
      if (f.is_open()) {
        f.read(buf, size);
        f.close();
      }
      else {
        return;
      }

      auto fbs_att_history = fbs::GetAttemptHistory(buf);
      auto fbs_atts = fbs_att_history->atts();

      resize(0);
      reserve(fbs_atts->size());
      for (auto fbs_att : *fbs_atts) {
        Attempt att;
        att.start_time = fbs_att->start_time();
        att.start_perc = fbs_att->start_perc();
        att.end_perc = fbs_att->end_per();
        att.flags = static_cast<Attempt::Flags>(fbs_att->flags());
        push_back(att);
      }

      debug();
    }

    void debug() {
      logger->debug("att. history [level id [{}], total atts. [{}]]", level_id, size());
    }
  };
}