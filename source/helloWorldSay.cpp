#include <fstream>
#include <JuceHeader.h>

using namespace std;
using namespace std::filesystem;

namespace HelloWorldSayExample {
  class Window1 : public DocumentWindow {
  public:
    Window1() : DocumentWindow {"Hello world (Say)", Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons} {
      setContentOwned(&mainComponent, false);
      setResizable(true, true);
      setBounds(200, 100, 300, 300);

      button1.setBounds(10, 10, 75, 25);
      button1.setButtonText("Say...");
      button1.onClick = [&] {
        Speak("Hello, World!");
      };
      
      mainComponent.addAndMakeVisible(&button1);
   }
    
  protected:
    void closeButtonPressed() override {JUCEApplication::quit();}
    
  private:
    // Very basic speech synthesizer using the command line.
    void Speak(const String& text) {
      #if JUCE_WINDOWS
        system(("powershell -Command \"Add-Type -AssemblyName System.Speech; (New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('" + text + "');\"").toRawUTF8());
      #endif
    }
    Component mainComponent;
    TextButton button1;
  };
  
  class Application : public JUCEApplication {
  protected:
    const String getApplicationName() override {return ProjectInfo::projectName;}
    const String getApplicationVersion() override {return ProjectInfo::versionString;}
    
    void initialise(const String&) override {mainWindow.setVisible(true);}
    void shutdown() override {}
    
  private:
    Window1 mainWindow;
  };
}

START_JUCE_APPLICATION(HelloWorldSayExample::Application)