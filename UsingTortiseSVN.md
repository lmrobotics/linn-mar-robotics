# Introduction #

Subversion combined with TortoiseSVN provides a convenient way to perform source control for any type of file. Source control is useful for saving versions of your work and recalling a specific version at a later date.  This quick start guild provides step by step instructions for getting started using TortoiseSVN and using for source control on Linn-Mar robotics projects.  [Click here for more comprehensive manual for TortoiseSVN](http://tortoisesvn.net/docs/release/TortoiseSVN_en/index.html)

# Details #

First you will need to install a Subversion client on your PC.  TortiseSVN is a popular and easy to use SVN client that is integrated into the windows explorer.  [Click Here to get TortiseSVN installer ](http://tortoisesvn.net/downloads.html)

Next you will need to get a check out of the Linn-Mar subversion repository. Right click inside a Windows explorer where you will want to place your checkout and click on **SVN Checkout...**

![http://linn-mar-robotics.googlecode.com/svn/wiki/images/checkout.png](http://linn-mar-robotics.googlecode.com/svn/wiki/images/checkout.png)

You will need to type the URL path to the Linn-Mar subversion repository.  Note you do probably will not want the entire trunk or branch directory. It is strongly encouraged that individuals work in the branches directory for items that are being edited by one individual.  Group efforts should be placed under trunk.  Finished products should be placed under the tags directory, such as code used for a competition. You can cut and past the following URL into the URL repository dialog box and then click **...** to navigate to the folder you really want to check out.

`https://linn-mar-robotics.googlecode.com/svn/branches`

![http://linn-mar-robotics.googlecode.com/svn/wiki/images/checkout2.png](http://linn-mar-robotics.googlecode.com/svn/wiki/images/checkout2.png)

You'll notice that the files in you new checkout have a green check-mark by them.  The green check-mark indicates that the file has not been modified.  As files are modified, the green check-mark changes to a red exclamation.

You can add files to the repository by creating new files within your checkout, right clicking on the file and navigating to TortoiseSVN->Add.

![http://linn-mar-robotics.googlecode.com/svn/wiki/images/add.png](http://linn-mar-robotics.googlecode.com/svn/wiki/images/add.png)

Once you have added or modified a file, you can commit your changes by right clicking on a file or a directory and then clicking on **SVN Commit**.  It is recommended that you check in your changes frequently so that you can get back to a known "working version" of you code or a known good version of your document.

![http://linn-mar-robotics.googlecode.com/svn/wiki/images/commit2.png](http://linn-mar-robotics.googlecode.com/svn/wiki/images/commit2.png)

Be sure to type a descriptive comment in the message box.  These comments show up in the revision history and will be useful when you want to get back to a specific version of your file.

![http://linn-mar-robotics.googlecode.com/svn/wiki/images/commit.png](http://linn-mar-robotics.googlecode.com/svn/wiki/images/commit.png)