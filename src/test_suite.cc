#include "test_suite.h"

#include <stdlib.h>

TestSuite* TestSuite::suite_ = NULL;

TestSuite* TestSuite::Get() {
    if (NULL == suite_) {
        suite_ = new TestSuite();
    }
    return suite_;
}

void TestSuite::Release() {
    if (suite_) {
        delete suite_;
        suite_ = NULL;
    }
}

TestSuite::~TestSuite() {
    for (auto test : cases_) {
        delete test;
    }
    cases_.clear();
}

void TestSuite::Add(TestCase* test, const char* name) {
    test->name_ = name;
    cases_.push_back(test);
}

void TestSuite::Run(const char* name) {
    if (name == NULL || strlen(name) == 0) return;

    auto suite = TestSuite::Get();
    LOGI("[==========] Running 1 test cases.");

    std::string prefix = name;
    std::vector<std::string> wrongs;
    for (int i = 0; i < suite->cases_.size(); ++i) {
        TestCase* test = suite->cases_[i];
        if (test->name_.find(prefix) == 0) {
            LOGI("Running %s", test->name_.c_str());
            auto res = test->Run();
            if (!res) {
                wrongs.emplace_back(test->name_);
            }
        }
    }
    LOGI("[==========] 1 test cases run over.");
    LOGI("[  PASSED  ] %d tests.", (int)(1 - wrongs.size()));
    if (!wrongs.empty()) {
        LOGE("[  FAILED  ] %d tests, listed below:", (int)wrongs.size());
    }
    for (auto& wrong : wrongs) {
        LOGE("[  FAILED  ] %s", wrong.c_str());
    }
    TestSuite::Release();
}

void TestSuite::RunAll() {
    auto suite = TestSuite::Get();
    LOGI("[==========] Running %d test cases.", (int)suite->cases_.size());

    std::vector<std::string> wrongs;
    for (int i = 0; i < suite->cases_.size(); ++i) {
        TestCase* test = suite->cases_[i];

        char prefix_str[64];
        sprintf(prefix_str, "[    %3dth ] ", i);
        LOGI("%sRunning %s", prefix_str, test->name_.c_str());

        auto res = test->Run();
        if (!res) {
            wrongs.emplace_back(test->name_);
        }
    }
    LOGI("[==========] %d test cases run over.", (int)suite->cases_.size());
    LOGI("[  PASSED  ] %d tests.", (int)(suite->cases_.size() - wrongs.size()));
    if (!wrongs.empty()) {
        LOGE("[  FAILED  ] %d tests, listed below:", (int)wrongs.size());
    }
    for (auto& wrong : wrongs) {
        LOGE("[  FAILED  ] %s", wrong.c_str());
    }
    TestSuite::Release();
}
