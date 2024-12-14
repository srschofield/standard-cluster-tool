#ifndef INCL_PARSER_H
#define INCL_PARSER_H

#include "Template.h"

class Parser {
  
private:
    
    Template *_template;
    
    int *_tlist;
    int _tcount;
    int _talloc;
    
    int _maxdepth;
    int _maxrow;
    int _maxdimer;
    
    int _bucklingtype;   // 0: p(2x1) flat; 1: p(2x2)+; 2: p(2x2)-; 3: c(4x2)+; 4: c(4x2)-

    int _output_format;     // 0: XYZ;  1: Gaussian

    bool _order_ascending;
    
    bool _order_hfirst;
    
    void _addToken(int token);
    
    int _readClusterDescriptor(char *descr);
    
    /** Reads single-digit or (via curly brackets) a multidigit positive number. A negative number is returned in case of an error condition.
     */
    
    static int _readNumber(char *str, int &idx);

    static int _readSingleDigitNumber(char *str, int &idx);

    static bool _strcmp(const char *a,const char *b);
        
public:

    Parser(void);
    
    ~Parser();

    int readArguments(int argc, char *argv[]);
    
    Template *getTemplate(void) {
        return _template;
    }
    
    int getTokenCount(void) const {
        return _tcount;
    }
    
    int getToken(const int idx) const {
        return _tlist[idx];
    }
    
    int getMaxDepth(void) const {
        return _maxdepth;
    }
    
    // Returns the largest width/number of rows of the cluster.
    
    int getMaxRow(void) const {
        return _maxrow;
    }
    
    int getMaxDimer(void) const {
        return _maxdimer;
    }
    
    int getBucklingOrientation(int row,int dimer);
    
    bool getOrderAscending(void) const {
        return _order_ascending;
    }
    
    bool getOrderHFirst(void) const {
        return _order_hfirst;
    }
    
    int getOutputFormat(void) const {
        return _output_format;
    };
    
    // Some static constants
    
    const static int XYZFormat; 
    const static int GaussianFormat; 
    
};

#endif
