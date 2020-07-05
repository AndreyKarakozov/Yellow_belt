#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

template <typename T>
ostream& operator << (ostream& os, const vector<T>& vi);

template <typename T>
ostream& operator << (ostream& os, const vector<T>& vi) {
  bool isfirst = true;
  for (const auto& element : vi) {
    if (!isfirst) {
      os << ' ';
    }
    isfirst = false;
    os << element;
  }
  return os;
}

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

istream& operator >> (istream& is, QueryType& query_type) {
  string input;
  is >> input;
  if (input == "NEW_BUS") {
    query_type = QueryType::NewBus;
  } else if (input == "BUSES_FOR_STOP") {
    query_type = QueryType::BusesForStop;
  } else if (input == "STOPS_FOR_BUS") {
    query_type = QueryType::StopsForBus;
  } else if (input ==  "ALL_BUSES") {
    query_type = QueryType::AllBuses;
  } else {
    const string msg = "Unknown query type: " + input;
    throw out_of_range(msg);
  }
  return is;
}

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  is >> q.type;
  switch (q.type) {
    case QueryType::NewBus:         //NEW_BUS bus stop_count stop1 stop2 ...
      is >> q.bus;
      int stop_count;
      is >> stop_count;
      q.stops.resize(stop_count);
      for (auto & current_stop : q.stops) {
        is >> current_stop;
      }
      break;
    case QueryType::BusesForStop:   //BUSES_FOR_STOP stop
      is >> q.stop;
      break;
    case QueryType::StopsForBus:    //STOPS_FOR_BUS bus
      is >> q.bus;
      break;
    case QueryType::AllBuses:       //ALL_BUSES
      break;
  }
  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (!r.buses.empty()) {
    os << r.buses << endl;
  } else {
    os << "No stop" << endl;
  }
  return os;
}

struct BusesForStop {
  string stop;
  vector<string> buses;
};

struct StopsForBusResponse {
  vector<BusesForStop> output;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  /* if bus1 exists:
   * Stop stop1: bus2 bus3
   * Stop stop2: bus4 bus5
   * Stop stop3: no interchange
   * Stop stop4: bus2
   * else: "No bus"
   */
  if (r.output.empty()) {
    os << "No bus" << endl;
  } else {
    for (const auto& i : r.output) {
      cout << "Stop " << i.stop << ": ";
      if (i.buses.empty()) {
        cout << "no interchange";
      } else {
        cout << i.buses;
      }
      cout << endl;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  /* if not empty:
   * bus1: stop1, stop2 ...
   * bus2: stop1, stop3 ...
   * else: "No buses"
   */
  if (r.buses_to_stops.size() == 0) {
    os << "No buses" << endl;
  } else {
    bool isfirst = true;
    for (const auto& bus_to_stops : r.buses_to_stops) {
      if (!isfirst) {
        os << endl;
      }
      isfirst = false;
      os << "Bus " << bus_to_stops.first << ": " << bus_to_stops.second << endl;
    }
    os << endl;
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse result;
    if (stops_to_buses.count(stop) == 0) {
      result.buses = {};
    } else {
      result.buses = stops_to_buses.at(stop);
    }
    return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse result;
    if (buses_to_stops.count(bus) == 0) {
      result.output = {};
    } else {
      for (const string& stop : buses_to_stops.at(bus)) {
        vector<string> buses;
        BusesForStop s;
        s.stop = stop;
        for (const string& other_bus : stops_to_buses.at(stop)) {
          if (bus != other_bus) {
            s.buses.push_back(other_bus);
          }
        }
        result.output.push_back(s);
      }
    }
    return result;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse result;
    result.buses_to_stops = buses_to_stops;
    return result;
  }

private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};


int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
