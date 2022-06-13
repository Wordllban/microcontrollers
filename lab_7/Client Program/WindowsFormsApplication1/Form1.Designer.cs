using System;
using System.IO.Ports;

namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.panelM = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.ComportSelectionBox = new System.Windows.Forms.ComboBox();
            this.OpenPortButton = new System.Windows.Forms.Button();
            this.SerialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.Slave1InfoTextField = new System.Windows.Forms.TextBox();
            this.ButtonGetInfoFromSlave1 = new System.Windows.Forms.Button();
            this.ButtonGetInfoFromSlave2 = new System.Windows.Forms.Button();
            this.Slave2InfoTextField = new System.Windows.Forms.TextBox();
            this.Slave1InfoStatusLabel = new System.Windows.Forms.Label();
            this.Slave2InfoStatusLabel = new System.Windows.Forms.Label();
            this.panelM.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelM
            // 
            this.panelM.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panelM.Controls.Add(this.label1);
            this.panelM.Controls.Add(this.ComportSelectionBox);
            this.panelM.Controls.Add(this.OpenPortButton);
            this.panelM.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelM.Location = new System.Drawing.Point(0, 0);
            this.panelM.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.panelM.Name = "panelM";
            this.panelM.Size = new System.Drawing.Size(797, 60);
            this.panelM.TabIndex = 19;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(175, 17);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 29);
            this.label1.TabIndex = 7;
            this.label1.Text = "COMPORT";
            // 
            // ComportSelectionBox
            // 
            this.ComportSelectionBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ComportSelectionBox.Location = new System.Drawing.Point(311, 14);
            this.ComportSelectionBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ComportSelectionBox.MaxDropDownItems = 10;
            this.ComportSelectionBox.Name = "ComportSelectionBox";
            this.ComportSelectionBox.Size = new System.Drawing.Size(130, 37);
            this.ComportSelectionBox.TabIndex = 6;
            this.ComportSelectionBox.Click += new System.EventHandler(this.ComportSelectionBox_Click);
            // 
            // OpenPortButton
            // 
            this.OpenPortButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OpenPortButton.Location = new System.Drawing.Point(457, 14);
            this.OpenPortButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.OpenPortButton.Name = "OpenPortButton";
            this.OpenPortButton.Size = new System.Drawing.Size(132, 39);
            this.OpenPortButton.TabIndex = 5;
            this.OpenPortButton.Tag = "1";
            this.OpenPortButton.Text = "Open";
            this.OpenPortButton.UseVisualStyleBackColor = true;
            this.OpenPortButton.Click += new System.EventHandler(this.OpenPortButton_Click);
            // 
            // SerialPort1
            // 
            this.SerialPort1.WriteBufferSize = 4096;
            // 
            // Slave1InfoTextField
            // 
            this.Slave1InfoTextField.Enabled = false;
            this.Slave1InfoTextField.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Slave1InfoTextField.Location = new System.Drawing.Point(29, 120);
            this.Slave1InfoTextField.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Slave1InfoTextField.Name = "Slave1InfoTextField";
            this.Slave1InfoTextField.ReadOnly = true;
            this.Slave1InfoTextField.Size = new System.Drawing.Size(511, 38);
            this.Slave1InfoTextField.TabIndex = 21;
            // 
            // ButtonGetInfoFromSlave1
            // 
            this.ButtonGetInfoFromSlave1.BackColor = System.Drawing.Color.Transparent;
            this.ButtonGetInfoFromSlave1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ButtonGetInfoFromSlave1.ForeColor = System.Drawing.Color.Black;
            this.ButtonGetInfoFromSlave1.Location = new System.Drawing.Point(566, 120);
            this.ButtonGetInfoFromSlave1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ButtonGetInfoFromSlave1.Name = "ButtonGetInfoFromSlave1";
            this.ButtonGetInfoFromSlave1.Size = new System.Drawing.Size(130, 46);
            this.ButtonGetInfoFromSlave1.TabIndex = 23;
            this.ButtonGetInfoFromSlave1.Text = "Slave1";
            this.ButtonGetInfoFromSlave1.UseVisualStyleBackColor = false;
            this.ButtonGetInfoFromSlave1.Visible = false;
            this.ButtonGetInfoFromSlave1.Click += new System.EventHandler(this.ButtonGetInfoFromSlave1_Click);
            // 
            // ButtonGetInfoFromSlave2
            // 
            this.ButtonGetInfoFromSlave2.BackColor = System.Drawing.Color.Transparent;
            this.ButtonGetInfoFromSlave2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ButtonGetInfoFromSlave2.ForeColor = System.Drawing.Color.Black;
            this.ButtonGetInfoFromSlave2.Location = new System.Drawing.Point(566, 194);
            this.ButtonGetInfoFromSlave2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ButtonGetInfoFromSlave2.Name = "ButtonGetInfoFromSlave2";
            this.ButtonGetInfoFromSlave2.Size = new System.Drawing.Size(130, 46);
            this.ButtonGetInfoFromSlave2.TabIndex = 25;
            this.ButtonGetInfoFromSlave2.Text = "Slave2";
            this.ButtonGetInfoFromSlave2.UseVisualStyleBackColor = false;
            this.ButtonGetInfoFromSlave2.Visible = false;
            this.ButtonGetInfoFromSlave2.Click += new System.EventHandler(this.ButtonGetInfoFromSlave2_Click);
            // 
            // Slave2InfoTextField
            // 
            this.Slave2InfoTextField.Enabled = false;
            this.Slave2InfoTextField.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Slave2InfoTextField.Location = new System.Drawing.Point(29, 202);
            this.Slave2InfoTextField.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Slave2InfoTextField.Name = "Slave2InfoTextField";
            this.Slave2InfoTextField.ReadOnly = true;
            this.Slave2InfoTextField.Size = new System.Drawing.Size(511, 38);
            this.Slave2InfoTextField.TabIndex = 24;
            // 
            // Slave1InfoStatusLabel
            // 
            this.Slave1InfoStatusLabel.AutoSize = true;
            this.Slave1InfoStatusLabel.Location = new System.Drawing.Point(35, 171);
            this.Slave1InfoStatusLabel.Name = "Slave1InfoStatusLabel";
            this.Slave1InfoStatusLabel.Size = new System.Drawing.Size(0, 20);
            this.Slave1InfoStatusLabel.TabIndex = 26;
            // 
            // Slave2InfoStatusLabel
            // 
            this.Slave2InfoStatusLabel.AutoSize = true;
            this.Slave2InfoStatusLabel.Location = new System.Drawing.Point(35, 253);
            this.Slave2InfoStatusLabel.Name = "Slave2InfoStatusLabel";
            this.Slave2InfoStatusLabel.Size = new System.Drawing.Size(0, 20);
            this.Slave2InfoStatusLabel.TabIndex = 27;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 286);
            this.Controls.Add(this.Slave2InfoStatusLabel);
            this.Controls.Add(this.Slave1InfoStatusLabel);
            this.Controls.Add(this.ButtonGetInfoFromSlave2);
            this.Controls.Add(this.Slave2InfoTextField);
            this.Controls.Add(this.ButtonGetInfoFromSlave1);
            this.Controls.Add(this.Slave1InfoTextField);
            this.Controls.Add(this.panelM);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panelM.ResumeLayout(false);
            this.panelM.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

   

        #endregion
        private System.Windows.Forms.Panel panelM;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox ComportSelectionBox;
        private System.Windows.Forms.Button OpenPortButton;
        private System.IO.Ports.SerialPort SerialPort1;
        private System.Windows.Forms.TextBox Slave1InfoTextField;
        private System.Windows.Forms.Button ButtonGetInfoFromSlave1;
        private System.Windows.Forms.Button ButtonGetInfoFromSlave2;
        private System.Windows.Forms.TextBox Slave2InfoTextField;
        private System.Windows.Forms.Label Slave1InfoStatusLabel;
        private System.Windows.Forms.Label Slave2InfoStatusLabel;
    }
}

