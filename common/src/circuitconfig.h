#ifndef CIRCUITCONFIG_H
#define CIRCUITCONFIG_H

#include <list>

class SRInfo;

class CircuitConfig {
public:
    CircuitConfig();
    ~CircuitConfig();

    std::list<SRInfo*> getInputs() const;
    std::list<SRInfo*> getOutputs() const;

private:
    void load();
    void validate();
    void initInputSr();
    void initOutputSr();

    std::list<SRInfo*> _inputs;
    std::list<SRInfo*> _outputs;
    SRInfo *_current;
};

#endif // CIRCUITCONFIG_H
