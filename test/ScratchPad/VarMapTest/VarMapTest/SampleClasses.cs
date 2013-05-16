namespace VarMapTest
{
    using System.Diagnostics;
    using Infra.Frmwrk;

    public class SampleClass1 : ISetup, IRun, IVerify, ICleanup
    {
        #region ICleanup Members

        public void Cleanup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IVerify Members

        public void Verify(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IRun Members

        public void Run(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region ISetup Members

        public void Setup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        public void Test(IContext ctx, int i)
        {
            ctx.Alw("test" + "   " + i);
        }
    }

    public class SampleClass2 : ISetup, IRun, IVerify, ICleanup
    {
        #region ICleanup Members

        public void Cleanup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IVerify Members

        public void Verify(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IRun Members

        public void Run(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region ISetup Members

        public void Setup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion
    }

    public class SampleClass3 : ISetup, IRun, IVerify, ICleanup
    {
        #region ICleanup Members

        public void Cleanup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IVerify Members

        public void Verify(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region IRun Members

        public void Run(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion

        #region ISetup Members

        public void Setup(IContext ctx)
        {
            StackFrame sf = new StackFrame();
            ctx.Alw(this.GetType().FullName + "." + sf.GetMethod().Name);
        }

        #endregion
    }
}
