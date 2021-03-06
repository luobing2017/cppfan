/*
 * Copyright (c) 2012-2013, chunquedong
 *
 * This file is part of cppfan project
 * Licensed under the GNU LESSER GENERAL PUBLIC LICENSE version 3.0
 *
 * History:
 *   2013-1-19  Jed Young  Creation
 */

#include "cppfan/util/Test.h"
#include "cppfan/text/String.h"

#include <vector>

CF_USING_NAMESPACE

TestRunner *TestRunner::instance = nullptr;

TestRunner &TestRunner::cur() {
  if (instance == nullptr) {
    instance = new TestRunner();
  }
  return *instance;
}

void TestRunner::run(const char *nameFilter) {
  long count = 0;
  this->errorCount = 0;
  this->successCount = 0;

  cf_Log_info("test", "start run test");

  for (Test &test : testList) {
    Str name = test.group;
    name = name + "_" + test.name;
    if (name.startsWith(nameFilter)) {
      cf_Log_info("test", "run: %s", name.c_str());
      test.func();
      ++count;
      cf_Log_info("test", "end: %s", name.c_str());
    }
  }

  cf_Log_info("test", "test end: fail %d, total %d, testcase %d", errorCount
              , errorCount+successCount, count);
  if (errorCount > 0) {
    cf_Log_info("test", "======== test FAIL ========");
  } else {
    cf_Log_info("test", "======== test SUCCESS ========");
  }
}
