import { FC, useCallback, useEffect, useState } from 'react';
import { TestCaseResultType } from '../core';
import { Filter, TestingContext } from './TestingContext';
import { PALETTE } from './palette';
import { ScrollView, StyleSheet, Text, View } from 'react-native';

const defaultTestingSummary: Record<TestCaseResultType | 'total', number> = {
  total: 0,
  pass: 0,
  fail: 0,
  broken: 0,
  example: 0,
  skipped: 0,
  waitingForTester: 0,
};

export const Tester: FC<{
  children: any;
  filter?: Filter;
}> = ({ children, filter }) => {
  const [testCaseResultTypeByTestCaseId, setTestCaseResultTypeByTestCaseId] =
    useState<Record<string, TestCaseResultType | 'unknown'>>({});
  const [testingSummary, setTestingSummary] = useState({
    ...defaultTestingSummary,
  });

  const registerTestCase = useCallback((testCaseId: string) => {
    setTestCaseResultTypeByTestCaseId((prev) => {
      if (testCaseId in prev) {
        console.warn(`Test ${testCaseId} already exists`);
      }
      return {
        ...prev,
        [testCaseId]: 'unknown',
      };
    });
    return () => {
      setTestCaseResultTypeByTestCaseId((prev) => {
        const newState = { ...prev };
        delete newState[testCaseId];
        return newState;
      });
    };
  }, []);

  const reportTestCaseResult = useCallback(
    (testCaseId: string, result: TestCaseResultType) => {
      setTestCaseResultTypeByTestCaseId((prev) => ({
        ...prev,
        [testCaseId]: result,
      }));
    },
    []
  );

  useEffect(() => {
    const newTestingSummary = { ...defaultTestingSummary };
    for (const [_testCaseId, testCaseResult] of Object.entries(
      testCaseResultTypeByTestCaseId
    )) {
      if (testCaseResult !== 'unknown') {
        newTestingSummary[testCaseResult]++;
      }
      newTestingSummary.total++;
    }
    setTestingSummary(newTestingSummary);
  }, [testCaseResultTypeByTestCaseId]);

  return (
    <TestingContext.Provider
      value={{ registerTestCase, reportTestCaseResult, filter: filter ?? {} }}
    >
      <View style={styles.testerContainer}>
        <ScrollView
          horizontal
          style={styles.summaryContainer}
          contentContainerStyle={{ alignItems: 'center', width: '100%' }}
        >
          <SummaryItem
            name='TOTAL'
            color={'white'}
            value={testingSummary.total}
          />
          <SummaryItem
            name='RUNNING'
            color={PALETTE.red}
            value={
              testingSummary.total -
              (testingSummary.pass +
                testingSummary.fail +
                testingSummary.waitingForTester +
                testingSummary.example +
                testingSummary.broken +
                testingSummary.skipped)
            }
          />
          <SummaryItem
            name='PASS'
            color={PALETTE.green}
            value={testingSummary.pass}
          />
          <SummaryItem
            name='MANUAL'
            color={PALETTE.blue}
            value={testingSummary.waitingForTester}
          />
          <SummaryItem
            name='SKIPPED'
            color={PALETTE.yellow}
            value={testingSummary.skipped}
          />
          <SummaryItem
            name='FAIL'
            color={PALETTE.red}
            value={testingSummary.fail}
          />
          <SummaryItem
            name='BROKEN'
            color={PALETTE.red}
            value={testingSummary.broken}
          />
          <SummaryItem
            name='EXAMPLES'
            color={PALETTE.gray}
            value={testingSummary.example}
          />
        </ScrollView>
        {children}
      </View>
    </TestingContext.Provider>
  );
};

const SummaryItem: FC<{
  name: string;
  color: string;
  value: number;
  onPress?: () => {};
}> = ({ name, color, value, onPress }) => {
  return (
    <View style={styles.summaryItemContainer} onTouchEnd={() => onPress?.()}>
      <Text
        style={[
          styles.summaryItemValue,
          { color: value > 0 ? color : PALETTE.gray },
        ]}
        numberOfLines={1}
      >
        {value}
      </Text>
      <Text style={styles.summaryItemName}>{name}</Text>
    </View>
  );
};

const styles = StyleSheet.create({
  testerContainer: {
    backgroundColor: '#222',
    paddingHorizontal: 8,
  },
  summaryContainer: {
    width: '100%',
    display: 'flex',
    flexDirection: 'row',
    paddingHorizontal: 8,
  },
  summaryItemContainer: {
    flex: 1,
    paddingHorizontal: 1,
  },
  summaryItemValue: {
    color: 'white',
    fontSize: 20,
    width: '100%',
    fontWeight: 'bold',
  },
  summaryItemName: {
    color: PALETTE.gray,
    width: '100%',
    fontSize: 8,
  },
});
