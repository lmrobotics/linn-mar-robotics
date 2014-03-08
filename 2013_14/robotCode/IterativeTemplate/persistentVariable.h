#ifndef PERSISTENT_VARIABLE_H
#define PERSISTENT_VARIABLE_H

#include "ioLib.h"

/**
 * Persistent variable class
 */
template <class variableType> class persistentVariable
{
   public:

      /** ***************************************************************************
      * \brief Constructor for class.  
      *
      * \param fileName Used to save value between power cycles and resets
      *
      * \param defaultValue value variable is set to initially of the file does not exist.
      *   
      *
      */
      persistentVariable(char* fileName, variableType defaultValue): 
         variable(defaultValue)
      {
         int fd = open(fileName, O_RDONLY, 0777);
         if (fd==ERROR)
         {
            variable = defaultValue;
            // file doesn't exist, create it.
            fd = open(fileName, O_CREAT, 0777);
            write(fd, (void*)&variable, sizeof(variableType));
            close(fd);
         }
         else
         {
            int size = read(fd, (void*)&variable, sizeof(variableType));
            close(fd);
         }

      } // constructor
      
      ~persistentVariable() {}
      
      /** ***************************************************************************
      * \brief Sets the variable to the specified value
      *
      */
      void Set(variableType value)
      {
         variable = value;
         int fd = open(fileName, O_WRONLY, 0777);
         write(fd, (void*)&variable, sizeof(variableType));
         close(fd);

      } // Set

      /** ***************************************************************************
      * \brief returns the value of the variable
      *
      */
      variableType Get()
      {
         return variable;
      }

   private:
      variableType variable;
      int offset;
      char* fileName;
};

#endif
