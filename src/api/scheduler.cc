// EPOS CPU Scheduler Component Implementation

#include <process.h>
#include <time.h>

__BEGIN_SYS
OStream cout;

// The following Scheduling Criteria depend on Alarm, which is not available at scheduler.h
template <typename ... Tn>
FCFS::FCFS(int p, Tn & ... an): Priority((p == IDLE) ? IDLE : Alarm::elapsed()) {}

EDF::EDF(const Microsecond & d, const Microsecond & p, const Microsecond & c, unsigned int): Real_Time_Scheduler_Common(Alarm::ticks(d), Alarm::ticks(d), Alarm::ticks(p), Alarm::ticks(c)) {
    cout << "\nPeriod:" << p  << "\n";
    cout << "Deadline:" << d  << "\n";
    cout << "Capacity:" << c  << "\n";
}

void EDF::update() {
    if((_priority >= PERIODIC) && (_priority < APERIODIC))
        _priority = Alarm::elapsed() + _deadline;
    
    cout << "\nPeriod:" << _period  << "\n";
    cout << "Deadline:" << _deadline  << "\n";
    cout << "Capacity:" << _capacity  << "\n";
    cout << Alarm::elapsed();
}


LLF::LLF(const Microsecond & d, const Microsecond & p, const Microsecond & c, unsigned int)
: Real_Time_Scheduler_Common(Alarm::ticks(d-c), Alarm::ticks(d), Alarm::ticks(p), Alarm::ticks(c)) {
    _start = Alarm::elapsed();
    _ended_last_execution = false;
}
 
void LLF::update(){
    if (_ended_last_execution) {
        //tempo_de_execucao = Alarm::elapsed() - _start;
        _start = Alarm::elapsed();
        _ended_last_execution = false;
    }
    _priority = _deadline - Alarm::elapsed() % _period - _capacity;

    //cout << "\nPeriod:" << _period  << "\n";
    //cout << "Deadline:" << _deadline  << "\n";
    cout << "Capacity:" << _capacity  << "\n";
}

// Since the definition of FCFS above is only known to this unit, forcing its instantiation here so it gets emitted in scheduler.o for subsequent linking with other units is necessary.
template FCFS::FCFS<>(int p);

__END_SYS
