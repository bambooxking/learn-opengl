#ifndef __TEST_SUITE_H__ 
#define __TEST_SUITE_H__ 

#include <string>
#include <vector>

class TestCase {
    friend class TestSuite;

public:
    virtual ~TestCase() = default;
    virtual bool Run() = 0;

protected:
    std::string name_;
};

class TestSuite {
public:
    ~TestSuite();

    static TestSuite* Get();
    static void Release();

public:
    void Add(TestCase* test, const char* name);
    static void RunAll();
    static void Run(const char* name);

private:
    static TestSuite* suite_;
    std::vector<TestCase*> cases_;
};

template <class Case>
class TestCaseRegister {
public:
    TestCaseRegister(const char* name) { TestSuite::Get()->Add(new Case, name); }
    ~TestCaseRegister() {}
};

#define TestSuiteRegister(Case, name) static TestCaseRegister<Case> __r##Case(#name)

#define LOGI(...) {fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#define LOGE(...) {fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}

#define ASSERT_TRUE(x)                                                  \
    {                                                                   \
        int res = (x);                                                  \
        if (!res) {                                                     \
            fprintf(stderr, "%s:%d Failure.\n", __FILE__, __LINE__);    \
            return false;                                               \
        }                                                               \
    }
#define EXPECT_EQ(x, y)                                                 \
    {                                                                   \
        double ret = (double)fabs((double)(x) - (double)(y));           \
        if (ret > 0.00001) {                                            \
            fprintf(stderr,                                             \
                    "%s:%d Failure. The difference between value_check and value is %lf, which %lf vs %lf.\n",  \
                    __FILE__, __LINE__, ret, (double)(x), (double)(y)); \
            return false;                                               \
        }                                                               \
    }
#define ASSERT_NEAR(x, y, e)                                                        \
    {                                                                               \
        double ret = (double)fabs((double)(x) - (double)(y));                       \
        if (ret > (e)) {                                                            \
            fprintf(stderr,                                                         \
                    "%s:%d Failure. The difference between value_check and value is %lf, which %f vs %f, and expect_near_val is %f\n",  \
                    __FILE__, __LINE__, ret, (float)(x), (float)(y), (float)(e));   \
            return false;                                                           \
        }                                                                           \
    }

#endif	// __TEST_SUITE_H__