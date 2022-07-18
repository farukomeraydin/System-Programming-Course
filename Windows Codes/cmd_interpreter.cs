using System;
using System.Collections.Generic

namespace CSD
{
    class App
    {
        public static void Main()
        {
            CommandPrompt cp = new CommandPrompt("CSD");
            cp.Run();
        }
    }

    public delegate void Proc();

    class CommandPrompt
    {
        private string m_prompt;
        private Dictionary<string, Proc> m_cmds;

        public CommandPrompt(string prompt)
        {
            m_prompt = prompt;

            m_cmds = new Dictionary<string, Proc>();
            m_cmds.Add("dir", ProcDir);
            m_cmds.Add("copy", ProcCopy);
            m_cmds.Add("rename", ProcRename);
        }

        private void ProcDir()
        {
            Console.WriteLine("dir command");
        }

        private void ProcCopy()
        {
            Console.WriteLine("copy command");
        }

        private void ProcRename()
        {
            Console.WriteLine("rename command");
        }

        public void Run()
        {
            string cmd;
            string[] prms;

            for(; ; )
            {
                Console.Write("{0}>", m_prompt);
                cmd = Console.ReadLine();
                prms = cmd.Split(new char[] { ' ', '\t' });
                if (prms[0] == "")
                    continue;
                if (prms[0] == "exit")
                    break;

                if (m_cmds.ContainsKey(prms[0])
                    m_cmds[prms[0]]();
                else
                    Console.WriteLine("command not found: {0}", prms[0]);
            }
        }
    }
}
