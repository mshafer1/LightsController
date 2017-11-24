namespace LightsController
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
            this.cbboxPorts = new System.Windows.Forms.ComboBox();
            this.main = new System.Windows.Forms.RadioButton();
            this.dither = new System.Windows.Forms.RadioButton();
            this.bound = new System.Windows.Forms.RadioButton();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.beat = new System.Windows.Forms.RadioButton();
            this.musicless = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.lblResponse = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cbboxPorts
            // 
            this.cbboxPorts.FormattingEnabled = true;
            this.cbboxPorts.Location = new System.Drawing.Point(13, 13);
            this.cbboxPorts.Name = "cbboxPorts";
            this.cbboxPorts.Size = new System.Drawing.Size(121, 21);
            this.cbboxPorts.TabIndex = 0;
            this.cbboxPorts.SelectedIndexChanged += new System.EventHandler(this.cbboxPorts_SelectedIndexChanged);
            // 
            // main
            // 
            this.main.AutoSize = true;
            this.main.Location = new System.Drawing.Point(140, 14);
            this.main.Name = "main";
            this.main.Size = new System.Drawing.Size(59, 17);
            this.main.TabIndex = 1;
            this.main.Text = "Default";
            this.toolTip1.SetToolTip(this.main, "The default 4x2 pattern");
            this.main.UseVisualStyleBackColor = true;
            this.main.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // dither
            // 
            this.dither.AutoSize = true;
            this.dither.Location = new System.Drawing.Point(140, 38);
            this.dither.Name = "dither";
            this.dither.Size = new System.Drawing.Size(53, 17);
            this.dither.TabIndex = 2;
            this.dither.Text = "Dither";
            this.toolTip1.SetToolTip(this.dither, "Treat all 8 as 1 group");
            this.dither.UseVisualStyleBackColor = true;
            this.dither.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // bound
            // 
            this.bound.AutoSize = true;
            this.bound.Location = new System.Drawing.Point(140, 62);
            this.bound.Name = "bound";
            this.bound.Size = new System.Drawing.Size(56, 17);
            this.bound.TabIndex = 3;
            this.bound.Text = "Bound";
            this.toolTip1.SetToolTip(this.bound, "Blink all 8 to the beat of the music");
            this.bound.UseVisualStyleBackColor = true;
            this.bound.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // beat
            // 
            this.beat.AutoSize = true;
            this.beat.Location = new System.Drawing.Point(140, 84);
            this.beat.Name = "beat";
            this.beat.Size = new System.Drawing.Size(47, 17);
            this.beat.TabIndex = 4;
            this.beat.Text = "Beat";
            this.toolTip1.SetToolTip(this.beat, "Dance all lights to the beat");
            this.beat.UseVisualStyleBackColor = true;
            this.beat.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // musicless
            // 
            this.musicless.AutoSize = true;
            this.musicless.Location = new System.Drawing.Point(140, 107);
            this.musicless.Name = "musicless";
            this.musicless.Size = new System.Drawing.Size(85, 17);
            this.musicless.TabIndex = 7;
            this.musicless.Text = "Independent";
            this.toolTip1.SetToolTip(this.musicless, "Ignore the music");
            this.musicless.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 62);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Device Response:";
            // 
            // lblResponse
            // 
            this.lblResponse.AutoSize = true;
            this.lblResponse.Location = new System.Drawing.Point(6, 79);
            this.lblResponse.Name = "lblResponse";
            this.lblResponse.Size = new System.Drawing.Size(0, 13);
            this.lblResponse.TabIndex = 6;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(226, 139);
            this.Controls.Add(this.musicless);
            this.Controls.Add(this.lblResponse);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.beat);
            this.Controls.Add(this.bound);
            this.Controls.Add(this.dither);
            this.Controls.Add(this.main);
            this.Controls.Add(this.cbboxPorts);
            this.HelpButton = true;
            this.Name = "Form1";
            this.Text = "Lights Controller";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbboxPorts;
        private System.Windows.Forms.RadioButton main;
        private System.Windows.Forms.RadioButton dither;
        private System.Windows.Forms.RadioButton bound;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.RadioButton beat;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblResponse;
        private System.Windows.Forms.RadioButton musicless;
    }
}

