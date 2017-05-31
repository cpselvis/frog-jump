/**
 * A simple dp problem: frog jump stairs.
 * To write a Node.js addon, and JS call Native code.
 *
 * author: cpselvis@gmail.com
 */
#include <node.h>
#include<vector>

/**
 * Native method, calculate all ways frog jump to a target stair.
 */
int climbStairs(int n) {
  std::vector<int> dp(n);

  dp[1] = 1;
  dp[2] = 2;

  for (int i = 3; i <= n; i ++ ) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

/**
 * Export native method jumpTo
 */
void JumpTo(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  // Check input type
  if (!args[0] -> IsNumber()) {
    isolate -> ThrowException(v8::Exception::TypeError(
      v8::String::NewFromUtf8(isolate, "Wrong arguments type!")));
  }

  int value = climbStairs(args[0] -> NumberValue());
  v8::Local<v8::Number> num = v8::Number::New(isolate, value);

  args.GetReturnValue().Set(num);
}

// init is entry point.
void init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "jumpTo", JumpTo);
}

NODE_MODULE(frog_jump, init);
