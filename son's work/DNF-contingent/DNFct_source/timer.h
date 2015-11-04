#ifndef TIME_H
#define TIME_H

struct TimeValue
{
  struct timeval m_start;
  struct timeval m_end;
  double m_value;
};

class Timer {
 public:
  map<int,TimeValue> m_timer;
 protected:
  double time(struct timeval start, struct timeval end) const {
    return ((double) ((end.tv_sec - start.tv_sec) + 
		    (end.tv_usec - start.tv_usec)/1000000.0)); 
  };
 public:
  void start(int timer) {
    map<int,TimeValue>::iterator it;
    TimeValue t;

    it = m_timer.find(timer);

    if (it == m_timer.end()) {
      t.m_value = 0;
      // timer does not exist, create one      
      it = m_timer.insert(map<int,TimeValue>::value_type(timer,t)).first;
    }

    gettimeofday(&it->second.m_start,NULL);
  };

  void end(int timer) {
    map<int,TimeValue>::iterator it;

    it = m_timer.find(timer);

    if (it == m_timer.end()) {
      // timer does not exist
      return;
    }    

    gettimeofday(&it->second.m_end,NULL);

    // update the current value
    it->second.m_value += time(it->second.m_start,it->second.m_end);
  };

  double time(int timer) const {
    map<int,TimeValue>::const_iterator it;
    
    it = m_timer.find(timer);    
    if (it == m_timer.end())
      return 0.0;
    
    return (it->second.m_value); 
  };
};
#endif
