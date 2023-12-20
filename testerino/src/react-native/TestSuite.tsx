import { FC, useContext } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import { TestSuiteContext } from './TestingContext';

export const TestSuite: FC<{ name: string; children: any }> = ({
  name,
  children,
}) => {
  const testSuiteContext = useContext(TestSuiteContext);
  const parentTestSuiteId = testSuiteContext?.testSuiteId;
  const depth = testSuiteContext?.depth ?? 0;

  return (
    <TestSuiteContext.Provider
      value={{
        testSuiteName: name,
        testSuiteId: `${
          parentTestSuiteId ? `${parentTestSuiteId}::` : ''
        }${name}`,
        depth: depth + 1,
      }}
    >
      <View style={styles.testSuiteContainer}>
        <Text
          style={[
            styles.testSuiteHeader,
            {
              fontSize: depth > 0 ? 12 : 16,
            },
          ]}
        >
          {name}
        </Text>
        {children}
      </View>
    </TestSuiteContext.Provider>
  );
};

const styles = StyleSheet.create({
  testSuiteContainer: {
    padding: 8,
  },
  testSuiteHeader: {
    width: '100%',
    fontWeight: 'bold',
    color: '#EEE',
  },
});
