import {View, ScrollView, Text} from 'react-native';
import {TestSuite, TestCase} from '@rnoh/testerino';
import React, {useState} from 'react';
import {Button, Modal} from '../components';

export function ScrollViewTest() {
  return (
    <TestSuite name="ScrollView">
      <TestCase itShould="render scroll view with different rounded corners">
        <View
          style={{
            width: '100%',
            height: 100,
            position: 'relative',
            overflow: 'hidden',
          }}>
          <ScrollView
            style={{
              width: '80%',
              height: '80%',
              borderWidth: 3,
              borderColor: 'firebrick',
              borderTopLeftRadius: 10,
              borderTopRightRadius: 20,
              borderBottomRightRadius: 30,
              borderBottomLeftRadius: 40,
              backgroundColor: 'beige',
            }}
            contentContainerStyle={{
              alignItems: 'center',
              justifyContent: 'center',
            }}
            scrollEventThrottle={16}>
            {new Array(3).fill(0).map((_, idx) => {
              return (
                <View
                  key={idx}
                  style={{
                    width: '100%',
                    height: 50,
                    backgroundColor: 'pink',
                    marginBottom: 50,
                  }}
                />
              );
            })}
          </ScrollView>
        </View>
      </TestCase>
      <TestCase itShould="change rectangles colors to green when releasing scroll">
        <Modal>
          <MomentumTestCase />
        </Modal>
      </TestCase>
    </TestSuite>
  );
}

function MomentumTestCase() {
  const [hasDragBegan, setHasDragBegan] = useState(0);
  const [hasDragEnded, setHasDragEnded] = useState(0);
  const [hasMomentumBegan, setHasMomentumBegan] = useState(0);
  const [hasMomentumEnded, setHasMomentumEnded] = useState(0);

  return (
    <>
      <Button
        label="Reset"
        onPress={() => {
          setHasDragBegan(0);
          setHasDragEnded(0);
          setHasMomentumBegan(0);
          setHasMomentumEnded(0);
        }}
      />
      <View style={{backgroundColor: 'white', width: '100%'}}>
        <Text style={{height: 16}}>hasMomentumBegan: {hasMomentumBegan}</Text>
        <Text style={{height: 16}}>hasMomentumEnded: {hasMomentumEnded}</Text>
        <Text style={{height: 16}}>hasDragBegan: {hasDragBegan}</Text>
        <Text style={{height: 16}}>hasDragEnded: {hasDragEnded}</Text>
      </View>

      <View style={{width: 200, height: 200}}>
        <ScrollView
          onScrollBeginDrag={() => {
            setHasDragBegan(p => p + 1);
          }}
          onScrollEndDrag={() => {
            setHasDragEnded(p => p + 1);
          }}
          onMomentumScrollBegin={() => {
            setHasMomentumBegan(p => p + 1);
          }}
          onMomentumScrollEnd={() => {
            setHasMomentumEnded(p => p + 1);
          }}>
          <View style={{backgroundColor: 'red', width: '100%', height: 150}} />
          <View style={{backgroundColor: 'blue', width: '100%', height: 150}} />
          <View
            style={{backgroundColor: 'green', width: '100%', height: 150}}
          />
          <View style={{backgroundColor: 'red', width: '100%', height: 150}} />
        </ScrollView>
      </View>
    </>
  );
}
