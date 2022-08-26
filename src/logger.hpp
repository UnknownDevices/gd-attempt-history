#pragma once

static std::string parse_current_date_time(std::string s) {
  time_t now = time(0);
#pragma warning(suppress: 4996) // annoying
  tm tstruct = *localtime(&now);
  char buf[80];

  if(s=="now")
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  else if(s=="date")
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
  return std::string(buf);
};

static void log(std::string msg) {
  std::string filePath = "C:/Users/Nikky/logs/gd-attempt-history.txt";
  std::string now = parse_current_date_time("now");
  std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
  ofs << now << '\t' << msg << '\n';
  ofs.close();
}
