import logging
from pathlib import Path
import ycm_core

DIR_OF_THIS_SCRIPT = Path( __file__ ).parent 
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.ino', '.m', '.mm' ]

logger = logging.getLogger('ycm-extra-conf') 
database = None

# You can set a directory with a lot of libraries to be search recursively here
lib_dirs_project = [
   'lib'
  ,'src'
]

flags_general = [
   '-Wall'
  ,'-Wextra'
  ,'-Werror'

  ,'-Wno-attributes'
  ,'-std=c++17'
]

compilation_database_folder = '.pio/build/uno/compile_commands.json'


def IsHeaderFile( filename ):
    return filename.suffix in [ '.h', '.hxx', '.hpp', '.hh' ]


def FindCorrespondingSourceFile( filename ):
    filename = Path(filename)
    if IsHeaderFile( filename ):
        for extension in SOURCE_EXTENSIONS:
            if filename.with_suffix(extension).exists():
                return filename.with_suffix(extension)
    return filename


def GetCompilationInfoFromCLS():
    include_flags = []
    cflags = []
    cxxflags = []
    
    ccls_path = DIR_OF_THIS_SCRIPT / '.ccls'
    if ccls_path.exists():
        for l in ccls_path.open('rt'):
            l = l.strip()
            if l.startswith('-I'):
                include_flags.append(l)
            if l.startswith('%c '):
                cflags.append(l[3:])
            if l.startswith('%cpp '):
                cflags.append(l[5:])
            if l.startswith('-D'):
                cflags.append(l)
                cxxflags.append(l)
    return include_flags, cflags, cxxflags


def Settings ( **kwargs ):
    # logger.setLevel(logging.DEBUG)
    logger.debug(kwargs)
    try: 
        import ycm_core

        global database
        if database is None and (DIR_OF_THIS_SCRIPT / compilation_database_folder).exists() :
            database = ycm_core.CompilationDatabase( str(DIR_OF_THIS_SCRIPT / compilation_database_folder ))
    except ImportError:
        ycm_core = None

    language = kwargs[ 'language' ]
  
    if language == 'cfamily':
      # If the file is a header, try to find the corresponding source file and
      # retrieve its flags from the compilation database if using one. This is
      # necessary since compilation databases don't have entries for header files.
      # In addition, use this source file as the translation unit. This makes it
      # possible to jump from a declaration in thetheader file to its definition
      # in the corresponding source file.
        filename = FindCorrespondingSourceFile( kwargs[ 'filename' ] )
        logger.debug(filename)

        include_flags, cflags, cxxflags = GetCompilationInfoFromCLS()

        return_flags = flags_general + include_flags + (cflags if filename.suffix.lower == '.c' else cxxflags)

        if not database:
            return {
                    'flags': return_flags,
                    'include_paths_relative_to_dir': str(DIR_OF_THIS_SCRIPT.resolve()),
                    'override_filename': filename
                    }

        compilation_info = database.GetCompilationInfoForFile( str(filename) )
        if not compilation_info.compiler_flags_:
            logger.info('No compilation info for {} return flags from .ccls'.format(filename))
            return {
                    'flags': return_flags,
                    'include_paths_relative_to_dir': str(DIR_OF_THIS_SCRIPT.resolve()),
                    'override_filename': filename
                    }

        # Bear in mind that compilation_info.compiler_flags_ does NOT return a
        # python list, but a "list-like" StringVec object.
        final_flags = list( compilation_info.compiler_flags_ )
        logger.debug(final_flags)

        return {
                'flags': final_flags,
                'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
                'override_filename': filename
                }


if __name__ == '__main__':
    print(Settings(filename='src/lesson2_running_light.cpp', language='cfamily'))

