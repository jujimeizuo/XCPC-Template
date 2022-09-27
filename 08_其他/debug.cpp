using std::string;
using std::to_string;
template <typename A, typename B>
std::string to_string(std::pair<A, B> p);
 
template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p);
 
std::string to_string(const std::string& s) {
  return '"' + s + '"';
}
 
std::string to_string(const char* s) {
  return to_string((std::string) s);
}
 
std::string to_string(bool b) {
  return (b ? "true" : "false");
}
 
std::string to_string(std::vector<bool> v) {
  bool first = true;
  std::string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
std::string to_string(std::bitset<N> v) {
  std::string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
std::string to_string(A v) {
  bool first = true;
  std::string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}


template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p) {
  return "(" + to_string(std::get<0>(p)) + ", " + to_string(std::get<1>(p)) + ", " + to_string(std::get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p) {
  return "(" + to_string(std::get<0>(p)) + ", " + to_string(std::get<1>(p)) + ", " + to_string(std::get<2>(p)) + ", " + to_string(std::get<3>(p)) + ")";
}
 
void debug_out() { std::cerr << std::endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  std::cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif


