import React, {useState} from 'react';

import {Pressable, StyleSheet, View} from 'react-native';

import {TestCase, TestSuite} from '@rnoh/testerino';

export function PressableTest() {
  return (
    <TestSuite name="Pressable">
      <TestCase
        itShould="handle short presses"
        initialState={{
          onPressIn: false,
          onPress: false,
        }}
        arrange={({setState}) => {
          return (
            <Pressable
              onPressIn={() => setState(prev => ({...prev, onPressIn: true}))}
              onPress={() => setState(prev => ({...prev, onPress: true}))}>
              <View style={styles.unpressed} />
            </Pressable>
          );
        }}
        assert={({expect, state}) => {
          expect(state).to.be.deep.eq({
            onPressIn: true,
            onPress: true,
          });
        }}
      />
      <TestCase
        itShould="handle long press"
        initialState={{
          onLongPress: false,
        }}
        arrange={({setState}) => {
          return (
            <Pressable onLongPress={() => setState({onLongPress: true})}>
              <View style={styles.unpressed} />
            </Pressable>
          );
        }}
        assert={({expect, state}) => {
          expect(state).to.be.deep.eq({
            onLongPress: true,
          });
        }}
      />
      <TestCase
        itShould="handle pressing out"
        initialState={{
          onPressOut: false,
        }}
        arrange={({setState}) => {
          return (
            <Pressable onPressOut={() => setState({onPressOut: true})}>
              <View style={styles.unpressed} />
            </Pressable>
          );
        }}
        assert={({expect, state}) => {
          expect(state).to.be.deep.eq({
            onPressOut: true,
          });
        }}
      />
      <TestCase
        itShould="inner view should not react to presses"
        initialState={{
          tested: false,
          pressed: false,
        }}
        arrange={({setState}) => {
          return (
            <Pressable
              onPress={() => setState(prev => ({...prev, tested: true}))}
              style={styles.pressed}>
              <Pressable
                onPress={() => setState(prev => ({...prev, pressed: true}))}
                style={styles.unpressed}
                disabled
              />
            </Pressable>
          );
        }}
        assert={({expect, state}) => {
          expect(state).to.be.deep.eq({
            tested: true,
            pressed: false,
          });
        }}
      />
      <TestCase
        itShould="change color to blue on hover"
        skip
        //https://gl.swmansion.com/rnoh/react-native-harmony/-/issues/417
      >
        <HoverView />
      </TestCase>
      <TestCase
        itShould="pass when blue background is pressed"
        initialState={false}
        arrange={({setState}) => (
          <View
            style={{
              backgroundColor: 'blue',
              alignSelf: 'center',
              position: 'relative',
            }}>
            <Pressable
              hitSlop={{top: 48, left: 48, bottom: 48, right: 48}}
              style={{
                width: 48,
                height: 48,
                backgroundColor: 'green',
                margin: 48,
              }}
              onPress={() => {
                setState(true);
              }}
            />
            <View
              style={{
                width: 48,
                height: 48,
                backgroundColor: 'red',
                position: 'absolute',
                top: 48,
                left: 48,
              }}
              onTouchEnd={e => {
                e.stopPropagation();
              }}
            />
          </View>
        )}
        assert={({expect, state}) => {
          expect(state).to.be.true;
        }}
      />
    </TestSuite>
  );
}

const HoverView = () => {
  const [hovered, setHovered] = useState(false);
  return (
    <Pressable
      onHoverIn={() => {
        setHovered(true);
        console.log('onHoverIn');
      }}
      onHoverOut={() => {
        setHovered(false);
        console.log('onHoverOut');
      }}
      style={{...styles.unpressed, backgroundColor: hovered ? 'blue' : 'red'}}
    />
  );
};

const styles = StyleSheet.create({
  unpressed: {
    width: 50,
    height: 50,
    backgroundColor: 'red',
  },
  pressed: {
    width: 100,
    height: 100,
    backgroundColor: 'blue',
    justifyContent: 'center',
    alignItems: 'center',
  },
  longPressed: {
    width: 300,
    height: 100,
    backgroundColor: 'green',
  },
  text: {
    height: 20,
    width: 200,
    fontSize: 14,
  },
});
