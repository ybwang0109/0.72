import { createContext } from 'react';
import { TestCaseResultType } from '../core';

export type TestCaseType = 'automated' | 'manual' | 'example';

export type Filter = {
  types?: TestCaseType[];
  tags?: string[];
};

export const TestingContext = createContext<
  | undefined
  | {
      registerTestCase: (testCaseId: string) => () => void;
      reportTestCaseResult: (
        testCaseId: string,
        result: TestCaseResultType
      ) => void;
      filter: Filter;
    }
>(undefined);

export const TestSuiteContext = createContext<
  undefined | { testSuiteName: string; testSuiteId: string; depth: number }
>(undefined);

export const TestCaseContext = createContext<
  undefined | { reportTestCaseResult: (result: TestCaseResultType) => void }
>(undefined);
