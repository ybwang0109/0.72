import { expect as expect_ } from 'chai';
import { useContext, useLayoutEffect } from 'react';
import {
  TestCaseContext,
  TestCaseType,
  TestSuiteContext,
  TestingContext,
} from './TestingContext';
import { ExampleTestCase, ExampleTestCaseProps } from './ExampleTestCase';
import { LogicalTestCase } from './LogicalTestCase';

import { ManualTestCase, SmartManualTestCaseProps } from './ManualTestCase';

export function TestCase<TState = undefined>({
  itShould,
  tags,
  ...otherProps
}: { itShould: string; skip?: boolean; tags?: string[] } & (
  | ExampleTestCaseProps
  | { fn: (utils: { expect: typeof expect_ }) => Promise<void> | void }
  | SmartManualTestCaseProps<TState>
)) {
  const { registerTestCase, reportTestCaseResult, filter } =
    useContext(TestingContext)!;
  const shouldRenderExample = 'children' in otherProps;
  const shouldRenderManualTestCase = 'arrange' in otherProps;

  const testCaseType: TestCaseType = shouldRenderExample
    ? 'example'
    : shouldRenderManualTestCase
    ? 'manual'
    : 'automated';

  const shouldBeIgnored =
    (filter.types &&
      filter.types.length > 0 &&
      !filter.types.includes(testCaseType)) ||
    (filter.tags &&
      filter.tags.length > 0 &&
      !(tags ?? []).some((tag) => filter.tags!.includes(tag)));
  const testSuiteId = useContext(TestSuiteContext)?.testSuiteId;
  const testCaseId = `${testSuiteId ?? ''}::${itShould}`;

  useLayoutEffect(() => {
    if (shouldBeIgnored) return;
    return registerTestCase(testCaseId);
  }, [testCaseId]);

  if (shouldBeIgnored) {
    return null;
  }

  return (
    <TestCaseContext.Provider
      value={{
        reportTestCaseResult: (result) => {
          reportTestCaseResult(testCaseId, result);
        },
      }}
    >
      {shouldRenderExample ? (
        <ExampleTestCase itShould={itShould} {...otherProps}>
          {otherProps.children}
        </ExampleTestCase>
      ) : shouldRenderManualTestCase ? (
        <ManualTestCase itShould={itShould} {...otherProps} />
      ) : (
        <LogicalTestCase name={itShould} {...otherProps} />
      )}
    </TestCaseContext.Provider>
  );
}
