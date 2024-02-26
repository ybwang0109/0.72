import ReactContext from './ReactContext';

/**
 * A context wrapper that always wraps Android Application {@link Context} and {@link
 * CatalystInstance} by extending {@link ReactContext}
 */
export class ReactApplicationContext extends ReactContext {
  // We want to wrap ApplicationContext, since there is no easy way to verify that application
  // context is passed as a param, we use {@link Context#getApplicationContext} to ensure that
  // the context we're wrapping is in fact an application context.
   constructor(context: Context) {
	 super(context);
   }
}