using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        string s = "";
        public static string Evaluate(string expression)
        {
            System.Data.DataTable table = new System.Data.DataTable();
            table.Columns.Add("expression", string.Empty.GetType(), expression);
            System.Data.DataRow row = table.NewRow();
            table.Rows.Add(row);
            return (string)row["expression"];
        }
        public Form1()
        {
            InitializeComponent();
        }

        private void numpad1_Click(object sender, EventArgs e)
        {
            s += "1";
            textBox1.Text = s;
        }

        private void sinbutton_Click(object sender, EventArgs e)
        {
            try
            {
                s = Math.Sin(double.Parse(Evaluate(s))).ToString();
                textBox1.Text = s;
                s = "";
            }
            catch (Exception exc)
            {
                textBox1.Text = "Invalid!";
                s = "";
            }
            
        }

        private void rootbutton_Click(object sender, EventArgs e)
        {
            try
            {
                s = Math.Sqrt(double.Parse(Evaluate(s))).ToString();
                textBox1.Text = s;
                s = "";
            }
            catch (Exception exc)
            {
                textBox1.Text = "Invalid!";
                s = "";
            }
        }

        private void equalbutton_Click(object sender, EventArgs e)
        {
            try
            {
                textBox1.Text = Evaluate(s);
                s = "";
            }
            catch (Exception exc)
            {
                textBox1.Text = "Invalid!";
                s = "";
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void mulbutton_Click(object sender, EventArgs e)
        {
            s += " * ";
            textBox1.Text = s;
        }

        private void subbutton_Click(object sender, EventArgs e)
        {
            s += " - ";
            textBox1.Text = s;
        }

        private void addbutton_Click(object sender, EventArgs e)
        {
            s += " + ";
            textBox1.Text = s;
        }

        private void divbutton_Click_1(object sender, EventArgs e)
        {
            s += " / ";
            textBox1.Text = s;
        }

        private void numpad2_Click(object sender, EventArgs e)
        {
            s += "2";
            textBox1.Text = s;
        }

        private void numpad3_Click(object sender, EventArgs e)
        {
            s += "3";
            textBox1.Text = s;
        }

        private void numpad4_Click(object sender, EventArgs e)
        {
            s += "4";
            textBox1.Text = s;
        }

        private void numpad5_Click(object sender, EventArgs e)
        {
            s += "5";
            textBox1.Text = s;
        }

        private void numpad6_Click(object sender, EventArgs e)
        {
            s += "6";
            textBox1.Text = s;
        }

        private void numpad7_Click(object sender, EventArgs e)
        {
            s += "7";
            textBox1.Text = s;
        }

        private void numpad8_Click(object sender, EventArgs e)
        {
            s += "8";
            textBox1.Text = s;
        }

        private void numpad9_Click(object sender, EventArgs e)
        {
            s += "9";
            textBox1.Text = s;
        }

        private void numpad0_Click(object sender, EventArgs e)
        {
            s += "0";
            textBox1.Text = s;
        }

        private void tanbutton_Click(object sender, EventArgs e)
        {
            try
            {
                s = Math.Tan(double.Parse(Evaluate(s))).ToString();
                textBox1.Text = s;
                s = "";
            }
            catch (Exception exc)
            {
                textBox1.Text = "Invalid!";
                s = "";
            }
        }

        private void logbutton_Click(object sender, EventArgs e)
        {
            try
            {
                s = Math.Log10(double.Parse(Evaluate(s))).ToString();
                textBox1.Text = s;
                s = "";
            }
            catch (Exception exc)
            {
                textBox1.Text = "Invalid!";
                s = "";
            }
        }
    }
}
