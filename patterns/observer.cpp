// INFO: Observer pattern
// When  many "observer" objects need to be notified
// of a change in a "subject" object
//
// TODO: The registration is described well
//    but need to inspect the update functionality
// - make sure the observer interface works with any class
// - same with subject
#include <list>
#include <vector>
using namespace std;

class Observer {
  void update();
};

// NOTE: Method 1: Aggregation
// - Concrete objects have a Subject/Observer in a field

class SubjectAgg {
private:
  // list of observers
  list<Observer> observers; // aggregates observers

protected:
  void update(temp, humidity, pressure) {} // called by WeatherObjectAgg

public:
  void RegisterObserver(Observer obs) { observers.push_back(obs); }
  // This is a nono if we want to use Subject or any class
  void RegisterObserver(DisplayDevice dd) { observers.push_back(dd.observer); }
  void RemoveObserver(Observer obs) {}
  void NotifyObserfers(){}; // Tell Observers to call GetState

  void GetState() {}
  // Alternatively:
  // void PushState() {}
  // Automatically push data to Devices
  // - but what if device is not on?
  // - then they just call GetState when they turn on.
};

class WeatherObjectAgg { // The Concrete Subject
  // pulls data from WeatherStation
private:
  int temp, humidity, pressure;

  // Some method of populating temp, humidity, pressure from instruments

public:
  SubjectAgg subject; // aggregates subject
  WeatherObjectAgg() : subject{new Subject} {}
  ~WeatherObjectAgg() { delete subject }
  // implementation we dont have to worry about
  // void get_humidity() { ws.get_humidity(); }
  // void get_temperature() { ws.get_temperature(); }
  void measurementsChanged() {
    subject.update(temp, humidity, pressure);

    // your code goes here

    // WARN: this code won't do - what if we have multiple displays
    // or different types of displays
    //
    // currentConditionsDisplay.update(temp, humidity, pressure);
    // statisticsDisplay.update(temp, humidity, pressure);
    // forecastDisplay.update(temp, humidity, pressure);

    // NOTE: this code will just notify the subject of an observer pattern
    // - this subject can notify all its observers
    //
    // subject.update();
  }
};

class DisplayDeviceAgg { // The Concrete Object
private:
  Observer observer; // Observer is aggregated into DisplayDevice

public:
  DisplayDevice() : observer{new Observer} {}

  // Displays data from WeatherObject
  // Can display current condiion, weather stats, or forecast
};

// NOTE: Method 2: Generalization (inheritance)
// Concrete Subject/Objects inherit Subject/Observer,
// which provide a stable interface
class SubjectGen {
private:
  // list of observers
  list<Observer> observers; // aggregates observers

protected:
  void update(temp, humidity, pressure) {} // called by WeatherObjectGen

public:
  void RegisterObserver(Observer obs) { observers.push_back(obs); }
  void RemoveObserver(Observer obs) {
    // find observer index in list and erase
  }
  void NotifyObserfers(){}; // Tell Observers to call GetState

  void GetState() {
    ;
    ;
  }
  // Alternatively:
  // void PushState() {}
  // Automatically push data to Devices
  // - but what if device is not on?
  // - then they just call GetState when they turn on.
};
//
// - WeatherObject depends on Subject having an update method
//      that takes t, h, p
class WeatherObjectGen : public SubjectGen { // The Concrete Subject
  // pulls data from WeatherStation
private:
  int temp, humidity, pressure;

  // Some method of populating temp, humidity, pressure from instruments

public:
  SubjectGen subject; // aggregates subject
  WeatherObjectGen() : subject{new Subject} {}
  ~WeatherObjectGen() { delete subject }
  // implementation we dont have to worry about
  // void get_humidity() { ws.get_humidity(); }
  // void get_temperature() { ws.get_temperature(); }
  void measurementsChanged() {
    subject.update(temp, humidity, pressure);

    // your code goes here

    // WARN: this code won't do - what if we have multiple displays
    // or different types of displays
    //
    // currentConditionsDisplay.update(temp, humidity, pressure);
    // statisticsDisplay.update(temp, humidity, pressure);
    // forecastDisplay.update(temp, humidity, pressure);

    // this code will just notify the subject of an observer pattern
    // - this subject can notify all its observers
    //
    // subject.update();
  }
};

class DisplayDeviceGen : public Observer {
private:
  // inherits update()
  // use this to update self state
public:
  DisplayDeviceGen() {} // no longer need to init Observer

  // Displays data from WeatherObject
  // Can display current condiion, weather stats, or forecast
};

int main(int argc, char *argv[]) {
  // *** Desired programmer experience: ***
  //
  // Simply register observer
  weather_object.RegisterObserver(display_device);
  //
  // calling measurementsChanged calls update on observers
  weather_object.measurementsChanged();

  // NOTE: Method 1: Aggregation (in action)
  // pros: more loosely coupled than inheritance
  // cons: super verbose without special methods

  WeatherObjectAgg weather_object_agg;
  SubjectAgg weather_service;

  vector<DisplayDeviceAgg> devices(10);
  for (auto a = devices.begin(); a != devices.end(); ++a) {
    // Alternative implementations:

    // weather_object passes observer to its Subject
    weather_object_agg.subject.RegisterObserver(a.observer);
    // if weather_object_agg has RegisterObserver()
    weather_object_agg.RegisterObserver(a.observer);
    // and if SubjectAgg has RegisterObserver(DisplayDeviceAgg foo)
    weather_object_agg.RegisterObserver(a);

    // weather_object must know a's class and to call its ober
    weather_object.RegisterObserver(a);
  }

  // NOTE: Method 2: Generalization (in action)
  // pros: succinct syntax
  // cons: inheritance means dependence

  WeatherObjectGen weather_object_gen;
  vector<DisplayDeviceGen> devices(10);
  for (auto a = devices.begin(); a != devices.end(); ++a) {

    weather_object_agg.RegisterObserver(a); // ooo clean!
  }

  // NOTE: Discussion:
  // Method 1: Aggregation (discussion)
  // - I don't like the verbose syntax required
  // - Having a RegisterObserver() in the ConcreteSubject that calls
  //   RegisterObserver in the Subject seems UNDRY, though stable
  //
  // NOTE: Method 2: Generalization (discussion)
  // - In this situation, it appears that inheritance works
  //   well. Changing the superclass causes recompilation, but
  //   as long as the interface is stable, requires no changes
  //   to the subclass.
  //
  // NOTE: Result: I like inheritance here. As long as superclass
  // keeps consistent interface, it has most succinct implementation.

  return 0;
}
