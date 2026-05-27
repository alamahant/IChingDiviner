#include"helpmenudialog.h"
#include <QApplication>
#include<QString>
HelpMenuDialog::HelpMenuDialog(HelpType type, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(getTitle(type));
    setModal(true);
    resize(600, 500);

    setupUI();
    loadContent(type);
}

void HelpMenuDialog::setupUI()
{
    m_layout = new QVBoxLayout(this);

    m_contentArea = new QTextEdit(this);
    m_contentArea->setReadOnly(true);
   m_contentArea->setAcceptRichText(true);


    m_closeButton = new QPushButton("Close", this);
    connect(m_closeButton, &QPushButton::clicked, this, &QDialog::accept);

    m_layout->addWidget(m_contentArea);
    m_layout->addWidget(m_closeButton);
}

void HelpMenuDialog::loadContent(HelpType type)
{
    QString content;

    switch (type) {
    case HelpType::About:
        content = getAboutContent();
        break;
    case HelpType::Features:
        content = getFeaturesContent();
        break;
    case HelpType::Instructions:
        content = getInstructionsContent();
        break;
    case HelpType::BestPractices:
        content = getBestPracticesContent();
        break;
    case HelpType::WhatsNew:
        content = getWhatsNewContent();
        break;
    case HelpType::Shortcuts:
        content = getShortcutsContent();
        break;
    case HelpType::Security:
        content = getSecurityContent();
        break;
    case HelpType::TwoFA:
        content = getTwoFAContent();
        break;
    case HelpType::DataManagement:
        content = getDataManagementContent();
        break;
    case HelpType::DownloadManagement:
        content = getDownloadManagerContent();
        break;
    case HelpType::onSitesAndSessions:
        content = getSitesSessionsContent();
        break;
    case HelpType::onSecurity:
        content = getOnSecurityContent();
        break;
    case HelpType::onNewStorageSystem:
        content = getOnNewStorageSystemContent();
        break;
    case HelpType::onNamedProfiles:
        content = getOnNamedProfilesContent();
        break;
    case HelpType::onChangelog:
        content = getChangelogContent();
        break;
    case HelpType::supportUs:
        content = getSupportusContent();
        break;
    }


    m_contentArea->setHtml(content);
}

QString HelpMenuDialog::getTitle(HelpType type)
{
    switch (type) {
    case HelpType::About: return "About BinauralPlayer";
    case HelpType::Features: return "Features";
    case HelpType::Instructions: return "Instructions";
    case HelpType::BestPractices: return "Best Practices";
    case HelpType::WhatsNew: return "What's New";
    case HelpType::Shortcuts: return "Keyboard Shortcuts";
    case HelpType::Security: return "Jasmine Security";
    case HelpType::TwoFA: return "Jasmine 2FA Utility";
    case HelpType::DataManagement: return "Jasmine Data Management";
    case HelpType::DownloadManagement: return "Jasmine Download Management";
    case HelpType::onSitesAndSessions: return "On Sites And Sessions";
    case HelpType::onSecurity: return "On Security";
    case HelpType::onNewStorageSystem: return "On the New Storage System";
    case HelpType::onNamedProfiles: return "On Shared Named Profiles";
    case HelpType::onChangelog: return "Changelog";

    case HelpType::supportUs: return "Support Us";

    default: return "Help";
    }
}

QString HelpMenuDialog::getBestPracticesContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;">

            <h1 style="color: #8e44ad; text-align: center; margin-bottom: 20px;">
                🧠 Best Practices for Binaural & Isochronic Audio
            </h1>

            <p>
                Brainwave entrainment is the practice of using rhythmic audio—such as binaural beats
                or isochronic tones—to gently guide the brain into specific states of relaxation,
                focus, meditation, or sleep. While extremely helpful when used correctly, it’s important
                to understand how it works and how to use it safely.
            </p>

            <h2 style="color: #3498db;">🌊 What Are Binaural Beats?</h2>
            <p>
                Binaural beats occur when you play slightly different frequencies in each ear.
                The brain detects the difference between the tones and begins synchronizing with
                the resulting “beat frequency.” This effect requires <strong>headphones</strong>.
            </p>

            <h2 style="color: #3498db;">⚡ What Are Isochronic Tones?</h2>
            <p>
                Isochronic tones are single, sharply-pulsed tones that turn on and off at a steady rhythm.
                They do *not* require headphones and are considered one of the strongest forms of
                brainwave entrainment.
            </p>

            <h2 style="color: #27ae60;">✨ Potential Benefits</h2>
            <ul style="padding-left: 20px;">
                <li>Deep relaxation and meditation assistance</li>
                <li>Improved focus and concentration</li>
                <li>Increased creativity and problem-solving</li>
                <li>Enhanced sleep and dream clarity</li>
                <li>Stress and anxiety reduction</li>
                <li>Mood balancing and emotional grounding</li>
            </ul>

            <h2 style="color: #c0392b;">⚠️ Safety & Dangers</h2>
            <ul style="padding-left: 20px;">
                <li>Do <strong>not</strong> use while driving or operating machinery</li>
                <li>Avoid high-intensity frequencies if you are prone to seizures or epilepsy</li>
                <li>Start with short sessions (10–15 minutes) before longer ones</li>
                <li>If you feel dizziness or discomfort, stop immediately</li>
                <li>Use comfortable volume levels—entrainment does not require loud audio</li>
                <li>Never force meditation states; let the brain shift naturally</li>
            </ul>

            <h2 style="color: #2980b9;">📜 Useful Frequency Lists</h2>
            <p>
                A large list of brainwave-related frequencies can be found here:
            </p>
            <ul style="padding-left: 20px;">
                <li><a href="https://www.lunarsight.com/freq.htm">https://www.lunarsight.com/freq.htm</a></li>
                <li><a href="https://docs.preterhuman.net/Brainwave/Cymatic_Frequency_Listing">https://docs.preterhuman.net/Brainwave/Cymatic_Frequency_Listing</a></li>
            </ul>

            <h2 style="color: #16a085;">🌿 Background Ambience</h2>
            <p>
                Atmospheric nature sounds greatly enhance the experience. High-quality,
                royalty-free ambient audio can be found at:
            </p>
            <p>
                <a href="https://pixabay.com/sound-effects/search/nature/">https://pixabay.com/sound-effects/search/nature/</a>
            </p>

            <h2 style="color: #8e44ad;">💡 Best Practices</h2>
            <ul style="padding-left: 20px;">
                <li>Use good headphones for binaural beats</li>
                <li>Use speakers or headphones for isochronic tones</li>
                <li>Meditate or sit comfortably during sessions</li>
                <li>Combine tones with relaxing ambience or maybe some relaxxing music for deeper immersion</li>
                <li>Choose frequencies appropriate for your goal (sleep, focus, creativity, etc.)</li>
                <li>Consistency matters—small daily sessions are better than long sporadic ones</li>
            </ul>

            <div style="background-color: #f8f9fa; padding: 15px; border-radius: 8px; margin-top: 25px; text-align: center;">
                <strong>
                    Brainwave entrainment is a powerful tool—use it mindfully, with intention,
                    and always listen to your body.
                </strong>
            </div>

        </div>
    )";
}



QString HelpMenuDialog::getWhatsNewContent()
{
    return R"(
<div style="font-family: Arial, sans-serif; line-height: 1.6; color: #e0e0e0;">
    <h1 style="color: #ffd700; text-align: center; margin-bottom: 20px;">☯ What's New in IChingDiviner 1.0.3</h1>



    <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin-bottom: 25px; border: 1px solid #404040;">
        <h2 style="color: #ffd700; margin-top: 0;">📅 May 27, 2026</h2>
        <p style="color: #cccccc; text-align: center;">Your personal I Ching journal and sharing companion.</p>
    </div>

    <div style="margin: 20px 0;">
        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">📔 Journal System</h3>
            <p style="color: #cccccc;">Every reading you save is automatically recorded in your personal journal:</p>
            <ul style="color: #cccccc;">
                <li><strong>Date browsing:</strong> Calendar view shows which days have entries</li>
                <li><strong>One-click reload:</strong> Load any past reading instantly</li>
                <li><strong>Personal notes:</strong> Add your reflections and insights to any entry</li>
                <li><strong>Complete history:</strong> Never lose track of your divinations</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">📤 Social Sharing</h3>
            <p style="color: #cccccc;">Share your readings with friends and fellow practitioners:</p>
            <ul style="color: #cccccc;">
                <li><strong>One-click capture:</strong> Screenshot your complete reading (coins + hexagrams)</li>
                <li><strong>Multiple platforms:</strong> Twitter/X, Facebook, Reddit, Telegram, WhatsApp, Instagram</li>
                <li><strong>Save locally:</strong> Export as image file</li>
                <li><strong>Copy to clipboard:</strong> Paste anywhere</li>
                <li><strong>Subtle watermark:</strong> "IChingDiviner" added to shared images</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">📖 Beautiful Hexagram Meanings</h3>
            <p style="color: #cccccc;">The Wilhelm translation now displays in rich, readable HTML format:</p>
            <ul style="color: #cccccc;">
                <li><strong>Color-coded sections:</strong> Judgment (green), Image (orange), Lines (blue)</li>
                <li><strong>Elegant typography:</strong> Georgia serif font for comfortable reading</li>
                <li><strong>Zoom support:</strong> Ctrl+mouse wheel to adjust text size</li>
                <li><strong>Clear hierarchy:</strong> Headers, paragraphs, and visual separation</li>
                <li><strong>Above/Below info:</strong> Chinese, symbolic, and alchemical elements displayed as badges</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🪙 Import Physical Toss Mode</h3>
            <p style="color: #cccccc;">Perfect for those who want to use real physical coins:</p>
            <ul style="color: #cccccc;">
                <li><strong>Toggle mode:</strong> "Import Physical Toss" button enables manual entry</li>
                <li><strong>Click coins:</strong> Flip each coin individually to match your physical toss</li>
                <li><strong>Set Result:</strong> Record the current coin state as a hexagram line</li>
                <li><strong>Complete hexagram:</strong> Build your reading one line at a time</li>
                <li><strong>Visual feedback:</strong> Checked button state shows when mode is active</li>
            </ul>
        </div>


<div style="font-family: Arial, sans-serif; line-height: 1.6; color: #e0e0e0;">
    <h1 style="color: #ffd700; text-align: center; margin-bottom: 20px;">☯ What's New in IChingDiviner 1.0.0</h1>


    <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin-bottom: 25px; border: 1px solid #404040;">
        <h2 style="color: #ffd700; margin-top: 0;">🚀 Initial Release — March 18, 2026</h2>
        <p style="color: #cccccc; text-align: center;">The ancient oracle, reimagined for the modern age.</p>
    </div>

    <div style="margin: 20px 0;">
        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🪙 Traditional Coin Toss</h3>
            <p style="color: #cccccc;">Authentic 3-coin divination with proper changing line mechanics. Manual line-by-line building or one-click auto toss.</p>
            <ul style="color: #cccccc;">
                <li><strong style="color: #ffd700;">Stable Yang (1)</strong> — Solid line</li>
                <li><strong style="color: #ffd700;">Stable Yin (0)</strong> — Broken line</li>
                <li><strong style="color: #ff6b6b;">Changing Yang (3)</strong> — Solid → Yin (red)</li>
                <li><strong style="color: #ff6b6b;">Changing Yin (2)</strong> — Broken → Yang (red)</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">📖 Complete Wilhelm Translation</h3>
            <p style="color: #cccccc;">Full public domain Wilhelm/Baynes translation for all 64 hexagrams:</p>
            <ul style="color: #cccccc;">
                <li>Hexagram names in English, Chinese, and pinyin</li>
                <li>Wilhelm Symbolic — Philosophical explanations</li>
                <li>The Judgment — Traditional oracular text with commentary</li>
                <li>The Image — Visual symbolism and metaphors</li>
                <li>Line-by-line interpretations for every position</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🎴 Dual Display Modes</h3>
            <ul style="color: #cccccc;">
                <li><strong>Mandala Mode:</strong> Unique seven-circle mandalas generated for each hexagram, each ring representing a line</li>
                <li><strong>Tarot Mode:</strong> Card-style display for personal deck images</li>
                <li><strong>Toggle:</strong> Ctrl+D switches between modes</li>
                <li><strong>Hover Zoom:</strong> Cards and mandalas zoom on hover for detail</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🤖 AI-Powered Interpretations</h3>
            <p style="color: #cccccc;">Optional integration with OpenAI-compatible APIs:</p>
            <ul style="color: #cccccc;">
                <li><strong>Supported:</strong> Groq (free), Mistral, OpenAI, Ollama (local), Together AI, DeepSeek</li>
                <li><strong>Context-aware:</strong> AI receives source hexagram, modified hexagram, changing lines, and your question</li>
                <li><strong>Markdown formatting:</strong> Beautifully formatted responses with headers and lists</li>
                <li><strong>Question system:</strong> Pose specific questions to guide the interpretation</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🎨 Visual Features</h3>
            <ul style="color: #cccccc;">
                <li><strong>Golden coins:</strong> ● Heads / ○ Tails in vibrant gold</li>
                <li><strong>Dark theme:</strong> Easy-on-the-eyes interface for extended contemplation</li>
                <li><strong>Dockable panels:</strong> Resizable meanings and AI panels</li>
                <li><strong>Splitter:</strong> Adjustable between coin area and hexagram display</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">💾 Data Management</h3>
            <ul style="color: #cccccc;">
                <li><strong>Save/Load (Ctrl+S / Ctrl+O):</strong> Complete divinations with lines, question, AI text</li>
                <li><strong>JSON format:</strong> Human-readable, easy to backup</li>
                <li><strong>Settings persistence:</strong> Remembers your preferences (tarot mode, deck, UI freeze)</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">🔧 Power Features</h3>
            <ul style="color: #cccccc;">
                <li><strong>Mouse entropy:</strong> "Enchanted Coins" mode collects mouse movements for true randomness</li>
                <li><strong>Custom decks:</strong> Import your own card images (Tools → Open Decks Folder)</li>
                <li><strong>Factory reset:</strong> One-click reset of all settings</li>
                <li><strong>UI freeze toggle:</strong> Prevent accidental clicks during AI processing</li>
            </ul>
        </div>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #ffd700;">
            <h3 style="color: #ffd700; margin-top: 0;">📦 First-Time Setup</h3>
            <ul style="color: #cccccc;">
                <li><strong>Download Meanings:</strong> One-time download of Wilhelm dataset (File → Download Meanings)</li>
                <li><strong>Configure AI (optional):</strong> Tools → AI Model Selector</li>
            </ul>
        </div>
    </div>

    <div style="background-color: #2a2a2a; padding: 20px; border-radius: 8px; text-align: center; margin-top: 30px; border: 1px solid #404040;">
        <h3 style="color: #ffd700; margin-top: 0;">🌟 Coming Soon</h3>
        <p style="color: #cccccc;">Future updates may include:</p>
        <ul style="color: #cccccc; text-align: left; display: inline-block;">
            <li>Additional translations</li>
            <li>More deck visualization options</li>
            <li>Advanced AI prompt customization</li>
            <li>Divination journal with history</li>
        </ul>
        <p style="color: #ffd700; margin-top: 20px;">☯ May your path be illuminated ☯</p>
    </div>
</div>
    )";
}
QString HelpMenuDialog::getShortcutsContent()
{
    return QString();  // TODO: Implement
}


QString HelpMenuDialog::getAboutContent() {
    return QString(R"(
        <div style="text-align: center; font-family: Arial, sans-serif; color: #e0e0e0;">
            <h1 style="color: #ffd700; margin-bottom: 10px;">☯ IChingDiviner</h1>
            <h3 style="color: #b0b0b0; margin-bottom: 20px;">Ancient Wisdom Meets Modern Technology</h3>
            <p style="font-size: 16px; margin-bottom: 20px; color: #cccccc;">
                A modern I-Ching divination application that brings the ancient Chinese oracle
                to your fingertips. Based on the authoritative Wilhelm/Baynes translation,
                IChingDiviner combines traditional coin-toss divination with optional AI-powered
                interpretations.
            </p>

            <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 20px 0; border: 1px solid #404040;">
                <p style="margin: 5px 0;"><strong style="color: #ffd700;">Version:</strong> <span style="color: #cccccc;">%1</span></p>
                <p style="margin: 5px 0;"><strong style="color: #ffd700;">Built with:</strong> <span style="color: #cccccc;">Qt Framework 6</span></p>
                <p style="margin: 5px 0;"><strong style="color: #ffd700;">Translation:</strong> <span style="color: #cccccc;">Richard Wilhelm / Cary F. Baynes (Public Domain)</span></p>
                <p style="margin: 5px 0;"><strong style="color: #ffd700;">License:</strong> <span style="color: #cccccc;">GPL-3.0</span></p>
            </div>

            <div style="margin: 30px 0;">
                <h4 style="color: #ffd700; border-bottom: 1px solid #404040; padding-bottom: 10px;">Key Features</h4>

                <div style="text-align: left; margin: 20px 30px; color: #cccccc;">
                    <p>• <strong style="color: #ffd700;">Traditional Coin Toss</strong> — Authentic 3-coin divination method with changing lines</p>
                    <p>• <strong style="color: #ffd700;">Complete Wilhelm Translation</strong> — Full hexagram meanings, judgments, images, and line interpretations</p>
                    <p>• <strong style="color: #ffd700;">Dual Visualization</strong> — Toggle between artistic mandalas and tarot-style card displays</p>
                    <p>• <strong style="color: #ffd700;">AI-Powered Interpretations</strong> — Optional integration with OpenAI-compatible APIs (Groq, Mistral, Ollama, etc.)</p>
                    <p>• <strong style="color: #ffd700;">Custom Decks</strong> — Import your own card images for personal use</p>
                    <p>• <strong style="color: #ffd700;">Save/Load Divinations</strong> — Preserve readings with questions and AI interpretations</p>
                    <p>• <strong style="color: #ffd700;">Mouse Entropy</strong> — Enhanced randomness through mouse movement collection</p>
                    <p>• <strong style="color: #ffd700;">Dark Theme</strong> — Easy-on-the-eyes interface for extended contemplation</p>
                </div>

                <p><strong style="color: #27ae60;">✓ Free for Linux on Flathub</strong></p>

                <p><strong>Windows & macOS Binaries:</strong><br>
                <a href="https://jnanadhakini.gumroad.com/l/qhuipk" style="color: #ffd700; text-decoration: none;">
                → https://jnanadhakini.gumroad.com/l/qhuipk</a></p>

                <p><strong>All Windows/macOS apps:</strong><br>
                <a href="https://jnanadhakini.gumroad.com" style="color: #ffd700; text-decoration: none;">
                → https://jnanadhakini.gumroad.com</a></p>

                <p><strong>Source Code & Linux Version:</strong><br>
                <a href="https://github.com/alamahant/IChingDiviner" style="color: #ffd700; text-decoration: none;">
                → https://github.com/alamahant/IChingDiviner</a></p>
            </div>

            <hr style="margin: 30px 0; border: 1px solid #404040;">

            <div style="margin: 20px 0;">
                <p style="margin: 5px 0; color: #b0b0b0;">
                    <strong style="color: #ffd700;">Copyright © 2025 Alamahant</strong>
                </p>
                <p style="margin: 5px 0; font-size: 12px; color: #808080;">
                    Licensed under GPL-3.0. Wilhelm/Baynes translation in public domain.
                </p>
                <p style="margin: 5px 0; font-size: 12px; color: #808080;">
                    Dataset compiled by Adam Blvck (MIT License)
                </p>
            </div>

            <div style="margin: 20px 0;">
                <p style="font-size: 14px; color: #b0b0b0;">
                    Crafted with ☯ for seekers of wisdom, philosophers, and the curious
                </p>
                <p style="font-size: 12px; color: #666666; margin-top: 30px;">
                    May the hexagrams guide your path
                </p>
            </div>
        </div>
    )").arg(QApplication::applicationVersion());
}


QString HelpMenuDialog::getFeaturesContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #e0e0e0;">
            <h1 style="color: #ffd700; text-align: center; margin-bottom: 20px;">IChingDiviner Features</h1>

            <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin-bottom: 25px; border: 1px solid #404040;">
                <h2 style="color: #ffd700; margin-top: 0;">Ancient Wisdom, Modern Technology</h2>
                <p style="color: #cccccc;">A complete I-Ching divination application featuring the authoritative Wilhelm/Baynes translation, traditional coin-toss mechanics, and optional AI-powered interpretations.</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">☯ Core Divination</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Traditional Coin Toss</h3>
                <p style="color: #cccccc;">Authentic 3-coin divination method with proper handling of changing yin/yang lines and resulting hexagram transformation.</p>

                <h3 style="color: #ffa500;">Manual & Auto Toss</h3>
                <p style="color: #cccccc;">Build your hexagram line by line with individual tosses or generate all six at once with auto-toss functionality.</p>

                <h3 style="color: #ffa500;">Enhanced Randomness</h3>
                <p style="color: #cccccc;">Optional mouse entropy collection for truly random seeds - move your mouse to gather entropy before tossing.</p>

                <h3 style="color: #ffa500;">Changing Lines</h3>
                <p style="color: #cccccc;">Visual distinction between stable and changing lines with color coding (red for changing lines).</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">📖 Wilhelm Translation</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Complete Hexagram Data</h3>
                <p style="color: #cccccc;">All 64 hexagrams with traditional Chinese names, pinyin, and English translations.</p>

                <h3 style="color: #ffa500;">Wilhelm Symbolic</h3>
                <p style="color: #cccccc;">In-depth philosophical explanations of each hexagram's meaning and significance.</p>

                <h3 style="color: #ffa500;">The Judgment</h3>
                <p style="color: #cccccc;">Traditional oracular text with Wilhelm's detailed commentary and interpretation.</p>

                <h3 style="color: #ffa500;">The Image</h3>
                <p style="color: #cccccc;">Visual symbolism and natural metaphors with explanatory notes.</p>

                <h3 style="color: #ffa500;">Line-by-Line Interpretations</h3>
                <p style="color: #cccccc;">Complete translations for all six lines, including changing line meanings and Wilhelm's commentary.</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🎴 Visualization</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Hexagram Display</h3>
                <p style="color: #cccccc;">Traditional stacked line visualization with clear distinction between yin (broken) and yang (solid) lines.</p>

                <h3 style="color: #ffa500;">Mandala Mode</h3>
                <p style="color: #cccccc;">Artistic seven-circle mandalas generated uniquely for each hexagram, with color-coded rings representing each line.</p>

                <h3 style="color: #ffa500;">Tarot Mode</h3>
                <p style="color: #cccccc;">Optional card-style display - import your own deck images for personal use.</p>

                <h3 style="color: #ffa500;">Custom Decks</h3>
                <p style="color: #cccccc;">Add your own card images to the decks folder for a personalized experience.</p>

                <h3 style="color: #ffa500;">Hover Zoom</h3>
                <p style="color: #cccccc;">Cards and mandalas zoom on hover for detailed viewing.</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🤖 AI Integration</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Multiple Provider Support</h3>
                <p style="color: #cccccc;">Compatible with any OpenAI-format API: Groq, Mistral, OpenAI, Ollama (local), Together AI, DeepSeek, and more.</p>

                <h3 style="color: #ffa500;">Context-Aware Prompts</h3>
                <p style="color: #cccccc;">AI receives complete divination data: source hexagram, resulting hexagram, changing lines, and your question.</p>

                <h3 style="color: #ffa500;">Markdown Formatting</h3>
                <p style="color: #cccccc;">AI responses are beautifully formatted with headers, bold text, and bullet points.</p>

                <h3 style="color: #ffa500;">Local Storage</h3>
                <p style="color: #cccccc;">API keys stored securely in system settings, never transmitted elsewhere.</p>

                <h3 style="color: #ffa500;">User Question</h3>
                <p style="color: #cccccc;">Pose specific questions to guide the AI interpretation.</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">💾 Data Management</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Save Divinations</h3>
                <p style="color: #cccccc;">Preserve complete readings including lines, question, AI interpretation, and deck preference.</p>

                <h3 style="color: #ffa500;">Load Divinations</h3>
                <p style="color: #cccccc;">Restore previous readings with full context - hexagram, question, and AI response.</p>

                <h3 style="color: #ffa500;">JSON Format</h3>
                <p style="color: #cccccc;">All saved data in human-readable JSON for easy backup and portability.</p>
            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🎨 User Interface</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Dark Theme</h3>
                <p style="color: #cccccc;">Easy-on-the-eyes dark interface designed for extended contemplation sessions.</p>

                <h3 style="color: #ffa500;">Dockable Panels</h3>
                <p style="color: #cccccc;">Hexagram meanings and AI interpretation in resizable, movable docks.</p>

                <h3 style="color: #ffa500;">Golden Coins</h3>
                <p style="color: #cccccc;">Visual coin toss display with heads (●) and tails (○) in vibrant gold.</p>

                <h3 style="color: #ffa500;">Keyboard Shortcuts</h3>
                <p style="color: #cccccc;">Quick access to all major functions: Ctrl+D toggles display mode, Ctrl+S saves, Ctrl+O loads.</p>

                <h3 style="color: #ffa500;">📔 Journal System</h3>
                <p style="color: #cccccc;">Every reading you save is automatically recorded with date browsing, personal notes, and one-click reloading of past divinations.</p>

                <h3 style="color: #ffa500;">📤 Social Sharing</h3>
                <p style="color: #cccccc;">Capture your complete reading as an image and share to social media, save locally, or copy to clipboard with a single click.</p>

                <h3 style="color: #ffa500;">📖 Rich Hexagram Display</h3>
                <p style="color: #cccccc;">Beautifully formatted Wilhelm translation with color-coded sections, elegant typography, and full text zoom support (Ctrl+mouse wheel).</p>

            </div>

            <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🔧 Technical Features</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #ffa500;">Cross-Platform</h3>
                <p style="color: #cccccc;">Available for Linux (Flatpak), Windows, and macOS.</p>

                <h3 style="color: #ffa500;">Settings Persistence</h3>
                <p style="color: #cccccc;">All preferences saved: tarot mode, deck selection, UI freeze behavior, and AI configurations.</p>

                <h3 style="color: #ffa500;">Factory Reset</h3>
                <p style="color: #cccccc;">One-click reset of all settings to defaults.</p>

                <h3 style="color: #ffa500;">Dataset Download</h3>
                <p style="color: #cccccc;">One-time download of Wilhelm translation dataset with proper attribution.</p>
            </div>

            <div style="background-color: #2a2a2a; padding: 20px; border-radius: 8px; text-align: center; margin-top: 30px; border: 1px solid #404040;">
                <h3 style="color: #ffd700; margin-top: 0;">The Oracle in Your Hands</h3>
                <p style="color: #cccccc; margin-bottom: 0;">IChingDiviner brings the ancient wisdom of the I-Ching to the digital age, combining traditional divination methods with modern technology for deeper insight and contemplation.</p>
            </div>
        </div>
    )";
}


QString HelpMenuDialog::getInstructionsContent()
{
    return R"(
<div style="font-family: Arial, sans-serif; line-height: 1.6; color: #e0e0e0;">
    <h1 style="color: #ffd700; text-align: center; margin-bottom: 20px;">How to Use IChingDiviner</h1>

    <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin-bottom: 25px; border: 1px solid #404040;">
        <h2 style="color: #ffd700; margin-top: 0;">☯ Overview</h2>
        <p style="color: #cccccc;">IChingDiviner brings the ancient wisdom of the I-Ching to your fingertips. The app follows the traditional 3-coin divination method, provides complete Wilhelm/Baynes translations, and offers optional AI-powered interpretations.</p>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🪙 Performing a Divination</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Method 1: Manual Toss (Line by Line)</h3>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li>Click <strong>"Toss"</strong> to throw three coins</li>
            <li>Each toss generates one line (from bottom to top)</li>
            <li>Coins display as gold circles: <strong>● (Heads)</strong> or <strong>○ (Tails)</strong></li>
            <li>Continue until all 6 lines are built</li>
            <li>The hexagram builds visually with each toss</li>
        </ul>

        <h3 style="color: #ffa500;">Method 2: Auto Toss (Full Hexagram)</h3>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li>Click <strong>"Auto Toss"</strong> to generate all 6 lines at once</li>
            <li>Each toss plays out in sequence</li>
            <li>The complete hexagram appears immediately</li>
        </ul>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border: 1px solid #404040;">
            <h3 style="color: #ffa500; margin-top: 0;">🔮 Understanding the Lines</h3>
            <p style="color: #cccccc;"><strong>Line Types:</strong></p>
            <ul style="padding-left: 20px; color: #cccccc;">
                <li><strong style="color: #ffd700;">Stable Yang (1)</strong> — Solid line, remains yang</li>
                <li><strong style="color: #ffd700;">Stable Yin (0)</strong> — Broken line, remains yin</li>
                <li><strong style="color: #ff6b6b;">Changing Yang (3)</strong> — Solid line that becomes yin (shown in red)</li>
                <li><strong style="color: #ff6b6b;">Changing Yin (2)</strong> — Broken line that becomes yang (shown in red)</li>
            </ul>
            <p style="color: #cccccc; margin-top: 10px;">Changing lines determine the resulting hexagram and are key to the interpretation.</p>
        </div>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">📖 Reading the Interpretation</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Source Hexagram</h3>
        <p style="color: #cccccc;">The hexagram formed by your coin toss appears on the left with:</p>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li>Hexagram number and name</li>
            <li>Chinese characters and pinyin</li>
            <li>Visual representation of the lines</li>
            <li>Mandala or tarot visualization (toggle with Ctrl+D)</li>
        </ul>

        <h3 style="color: #ffa500;">Modified Hexagram</h3>
        <p style="color: #cccccc;">If changing lines exist, the resulting hexagram appears on the right, showing how the situation may evolve.</p>

        <h3 style="color: #ffa500;">Hexagram Meaning Panel (Right Dock)</h3>
        <p style="color: #cccccc;">The complete Wilhelm translation including:</p>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li><strong>Wilhelm Symbolic</strong> — Philosophical explanation of the hexagram</li>
            <li><strong>The Judgment</strong> — Traditional oracular text with commentary</li>
            <li><strong>The Image</strong> — Visual symbolism and natural metaphors</li>
            <li><strong>Line Interpretations</strong> — Detailed meanings for each line, especially important for changing lines</li>
        </ul>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🤖 AI Interpretations</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Setup</h3>
        <ol style="padding-left: 20px; color: #cccccc;">
            <li>Go to <strong>Tools → AI Model Selector</strong></li>
            <li>Click <strong>"Add"</strong> and configure your preferred AI provider</li>
            <li>Supported: Groq, Mistral, OpenAI, Ollama (local), etc.</li>
            <li>Set the model as <strong>"Active"</strong></li>
        </ol>

        <h3 style="color: #ffa500;">Usage</h3>
        <ol style="padding-left: 20px; color: #cccccc;">
            <li><strong>Set a Question (Optional)</strong> — Click "Set Question" to focus the interpretation</li>
            <li>Complete your hexagram</li>
            <li>Click <strong>"Get AI Interpretation"</strong> in the Controls panel</li>
            <li>The AI receives: source hexagram, modified hexagram, changing lines, and your question</li>
            <li>Response appears formatted with markdown in the AI panel</li>
        </ol>

        <div style="background-color: #2a2a2a; padding: 15px; border-radius: 8px; margin: 15px 0; border: 1px solid #404040;">
            <h3 style="color: #ffa500; margin-top: 0;">💡 Tips for Best Results</h3>
            <ul style="padding-left: 20px; color: #cccccc;">
                <li>Ask clear, specific questions</li>
                <li>Use Groq's Llama 3.3 70B for deep philosophical interpretations</li>
                <li>Try Ollama locally for free, private interpretations</li>
                <li>Adjust temperature in model settings (0.7 recommended)</li>
            </ul>
        </div>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🎴 Display Modes</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Toggle Display (Ctrl+D)</h3>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li><strong>Mandala Mode (Square)</strong> — Artistic seven-circle mandalas, each ring representing a line</li>
            <li><strong>Tarot Mode (Rectangular)</strong> — Card-style display for personal deck images</li>
        </ul>

        <h3 style="color: #ffa500;">Importing Custom Decks</h3>
        <ol style="padding-left: 20px; color: #cccccc;">
            <li>Go to <strong>Tools → Open Decks Folder</strong></li>
            <li>Create a folder with your deck name (e.g., "Rider-Waite")</li>
            <li>Add numbered images: 00.png to 63.png (Hexagram 1 to 64)</li>
            <li>Select your deck from the dropdown in Controls panel</li>
        </ol>
        <p style="color: #808080; font-style: italic;">Note: For personal use with your own physical decks only.</p>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">💾 Saving & Loading</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Save Divination (Ctrl+S)</h3>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li>Saves complete reading: lines, question, AI interpretation, deck preference</li>
            <li>Stored as JSON in the save directory</li>
        </ul>

        <h3 style="color: #ffa500;">Load Divination (Ctrl+O)</h3>
        <ul style="padding-left: 20px; color: #cccccc;">
            <li>Restores previous reading with full context</li>
            <li>Hexagram displays, meanings, and AI text are restored</li>
        </ul>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🖱️ Interface Tips</h2>

    <div style="margin: 20px 0;">
        <ul style="padding-left: 20px; color: #cccccc;">
            <li><strong>Docks can be resized</strong> — Drag the edges of meaning and AI panels</li>
            <li><strong>Docks can be closed/moved</strong> — Use the dock handles to reposition</li>
            <li><strong>Hover to zoom</strong> — Cards and mandalas zoom on hover for detail</li>
            <li><strong>Splitter adjustable</strong> — Drag between coin area and hexagram display</li>
        </ul>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🔧 Settings & Preferences</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">UI Freeze During AI</h3>
        <p style="color: #cccccc;">Toggle in View menu — Prevents accidental clicks while AI generates response</p>

        <h3 style="color: #ffa500;">Enhanced Randomness</h3>
        <p style="color: #cccccc;">Click "Enchanted Coins" and move your mouse to collect entropy for truly random seeds</p>

        <h3 style="color: #ffa500;">Factory Reset</h3>
        <p style="color: #cccccc;">Tools → Factory Reset — Resets all settings to defaults (doesn't delete saved divinations)</p>
    </div>

    <h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">📥 First-Time Setup</h2>

    <div style="margin: 20px 0;">
        <h3 style="color: #ffa500;">Download Hexagram Meanings</h3>
        <p style="color: #cccccc;">File → Download Meanings — One-time download of the Wilhelm translation dataset (MIT licensed)</p>

        <h3 style="color: #ffa500;">Configure AI (Optional)</h3>
        <p style="color: #cccccc;">Tools → AI Model Selector — Set up your preferred AI provider</p>
    </div>


<h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🪙 Import Physical Toss</h2>

<div style="margin: 20px 0;">
    <h3 style="color: #ffa500;">Manual Coin Entry Mode</h3>
    <p style="color: #cccccc;">Click "Import Physical Toss" to toggle manual mode — click on each coin to flip it, then press "Set Result" to record the line. Perfect for using real physical coins in your divination practice.</p>

    <h3 style="color: #ffa500;">Build Line by Line</h3>
    <p style="color: #cccccc;">Match your physical toss by clicking coins to heads or tails, then record each line. Complete your hexagram one authentic toss at a time.</p>
</div>

<h2 style="color: #ffd700; border-bottom: 2px solid #ffd700; padding-bottom: 5px;">🔍 Text Zoom Feature</h2>

<div style="margin: 20px 0;">
    <h3 style="color: #ffa500;">Ctrl + Mouse Wheel</h3>
    <p style="color: #cccccc;">In the Hexagram Meaning panel, hold Ctrl and scroll your mouse wheel to zoom text in or out. Adjust the font size to your comfort for easier reading of the Wilhelm translation.</p>
</div>


    <div style="background-color: #2a2a2a; padding: 20px; border-radius: 8px; text-align: center; margin-top: 30px; border: 1px solid #404040;">
        <h3 style="color: #ffd700; margin-top: 0;">🌟 Quick Tips</h3>
        <ul style="text-align: left; padding-left: 40px; color: #cccccc;">
            <li><strong>Download meanings first</strong> — Required for hexagram interpretations</li>
            <li><strong>Use mouse entropy</strong> — For truly random divinations</li>
            <li><strong>Save important readings</strong> — JSON format preserves everything</li>
            <li><strong>Experiment with display modes</strong> — Ctrl+D toggles between mandalas and cards</li>
            <li><strong>Ask focused questions</strong> — Better AI interpretations</li>
        </ul>
    </div>
</div>
    )";
}

QString HelpMenuDialog::getSecurityContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;">
            <h1 style="color: #e74c3c; text-align: center; margin-bottom: 20px;">🔐 Security Features</h1>

            <div style="background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin-bottom: 25px;">
                <h2 style="color: #2c3e50; margin-top: 0;">Master Password Protection</h2>
                <p>Jasmine includes a comprehensive security system to protect your saved websites, sessions, and sensitive data.</p>
            </div>

            <h2 style="color: #3498db; border-bottom: 2px solid #3498db; padding-bottom: 5px;">🛡️ Password Protection Features</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Master password requirement on startup</li>
                    <li>Secure password hashing with salt encryption</li>
                    <li>Failed attempt protection (5 attempts maximum)</li>
                    <li>Factory reset option for forgotten passwords</li>
                </ul>
            </div>

            <h2 style="color: #27ae60; border-bottom: 2px solid #27ae60; padding-bottom: 5px;">🔧 How to Enable Password Protection</h2>

            <div style="margin: 20px 0;">
                <ol style="margin: 10px 0; padding-left: 25px;">
                    <li>Go to Security menu → "Require Password on Startup"</li>
                    <li>Read the security notice and click OK</li>
                    <li>Enter your new master password</li>
                    <li>Confirm your password</li>
                    <li>Jasmine will now require this password on every startup</li>
                </ol>
            </div>

            <div style="background-color: #fff3cd; padding: 15px; border-radius: 8px; margin: 15px 0;">
                <h3 style="color: #856404; margin-top: 0;">⚠️ Important Security Notes</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Choose a strong, memorable password</li>
                    <li>Write it down in a safe place</li>
                    <li>If you forget it, you'll need to factory reset</li>
                    <li>Password is encrypted and stored securely</li>
                </ul>
            </div>

            <h2 style="color: #f39c12; border-bottom: 2px solid #f39c12; padding-bottom: 5px;">🔄 Changing Your Master Password</h2>

            <div style="margin: 20px 0;">
                <ol style="margin: 10px 0; padding-left: 25px;">
                    <li>Go to Security menu → "Change Master Password"</li>
                    <li>Enter your new password</li>
                    <li>Confirm the new password</li>
                    <li>Password is updated immediately</li>
                </ol>
            </div>

            <h2 style="color: #e74c3c; border-bottom: 2px solid #e74c3c; padding-bottom: 5px;">🚨 Failed Login Protection</h2>

            <div style="margin: 20px 0;">
                <p><strong>Maximum 5 password attempts allowed</strong></p>
                <p>After 5 failed attempts, you get two options:</p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Exit Application</strong></li>
                    <li><strong>Factory Reset</strong> (clears all data and security settings)</li>
                </ul>
            </div>

            <h2 style="color: #9b59b6; border-bottom: 2px solid #9b59b6; padding-bottom: 5px;">🔄 Factory Reset</h2>

            <div style="margin: 20px 0;">
                <p>If you forget your master password, factory reset will:</p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Remove all security settings</li>
                    <li>Clear the master password</li>
                    <li>Reset password protection to disabled</li>
                    <li>Allow you to start fresh</li>
                </ul>
            </div>

            <h2 style="color: #1abc9c; border-bottom: 2px solid #1abc9c; padding-bottom: 5px;">⚙️ Security Menu Options</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>"Require Password on Startup"</strong> - Toggle password protection on/off</li>
                    <li><strong>"Change Master Password"</strong> - Update your existing password</li>
                </ul>
            </div>

            <h2 style="color: #e67e22; border-bottom: 2px solid #e67e22; padding-bottom: 5px;">🔒 Protection States</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #d35400;">When Password Protection is Active:</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Jasmine prompts for password on every startup</li>
                    <li>All your websites, sessions, and data remain encrypted</li>
                    <li>No access to application features without correct password</li>
                </ul>

                <h3 style="color: #d35400;">When Password Protection is Disabled:</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Jasmine starts immediately without password prompt</li>
                    <li>All features accessible without authentication</li>
                    <li>Data remains saved but unprotected</li>
                </ul>
            </div>

            <h2 style="color: #16a085; border-bottom: 2px solid #16a085; padding-bottom: 5px;">💡 Best Practices</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Use a unique password not used elsewhere</li>
                    <li>Include numbers, letters, and special characters</li>
                    <li>Avoid easily guessable information</li>
                    <li>Keep a secure backup of your password</li>
                    <li>Enable password protection if you store sensitive login information</li>
                </ul>
            </div>

            <h2 style="color: #8e44ad; border-bottom: 2px solid #8e44ad; padding-bottom: 5px;">🔐 Security Implementation</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>SHA-256 encryption with custom salt</li>
                    <li>No plain text password storage</li>
                    <li>Secure settings storage</li>
                    <li>Memory-safe password handling</li>
                </ul>
            </div>

            <div style="background-color: #d1ecf1; padding: 15px; border-radius: 8px; margin: 25px 0;">
                <h3 style="color: #0c5460; margin-top: 0;">🛡️ Complete Protection</h3>
                <p style="margin-bottom: 0;">This security system ensures your browsing profiles, saved websites, sessions, and any stored login references remain protected even if someone gains access to your computer.</p>
            </div>
        </div>
    )";
}

QString HelpMenuDialog::getTwoFAContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;">
            <h1 style="color: #e74c3c; text-align: center; margin-bottom: 20px;">🔐 2FA Code Generator</h1>

            <div style="background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin-bottom: 25px;">
                <h2 style="color: #2c3e50; margin-top: 0;">Two-Factor Authentication Manager</h2>
                <p>Jasmine includes a built-in Two-Factor Authentication (2FA) code generator that helps you manage and generate time-based one-time passwords (TOTP) for your accounts.</p>
            </div>

            <h2 style="color: #3498db; border-bottom: 2px solid #3498db; padding-bottom: 5px;">❓ What is 2FA?</h2>

            <div style="margin: 20px 0;">
                <p>Two-Factor Authentication adds an extra layer of security to your accounts by requiring a second form of verification beyond just your password. This usually involves a 6-digit code that changes every 30 seconds.</p>
            </div>

            <h2 style="color: #27ae60; border-bottom: 2px solid #27ae60; padding-bottom: 5px;">🚀 Key Features</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Generate 6-digit TOTP codes for any 2FA-enabled account</li>
                    <li>Real-time code updates every 30 seconds</li>
                    <li>Visual countdown timer showing when codes refresh</li>
                    <li>One-click code copying to clipboard</li>
                    <li>Secure local storage of account secrets</li>
                    <li>Support for multiple accounts from different services</li>
                </ul>
            </div>

            <h2 style="color: #f39c12; border-bottom: 2px solid #f39c12; padding-bottom: 5px;">📱 How to Access</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Open the 2FA Manager from the Toolbar icon or the Tools Menu</li>
                    <li>The manager opens in a separate window</li>
                    <li>Resizable interface with accounts list and code display</li>
                </ul>
            </div>

            <h2 style="color: #9b59b6; border-bottom: 2px solid #9b59b6; padding-bottom: 5px;">➕ Adding 2FA Accounts</h2>

            <div style="margin: 20px 0;">
                <ol style="margin: 10px 0; padding-left: 25px;">
                    <li>Click "Add Account" button</li>
                    <li>Enter account name (e.g., "GitHub", "Google", "Discord")</li>
                    <li>Paste the secret key from the website's 2FA setup</li>
                    <li>Optionally enter the issuer/company name</li>
                    <li>Click OK to save</li>
                </ol>
            </div>

            <div style="background-color: #fff3cd; padding: 15px; border-radius: 8px; margin: 15px 0;">
                <h3 style="color: #856404; margin-top: 0;">🔍 Where to Find Secret Keys</h3>
                <p>When enabling 2FA on websites, they typically show:</p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>A QR code for mobile apps</li>
                    <li>A text secret key (what you need for Jasmine)</li>
                    <li>Look for "Can't scan QR code?" or "Manual entry" options</li>
                </ul>
            </div>

            <h2 style="color: #e74c3c; border-bottom: 2px solid #e74c3c; padding-bottom: 5px;">🔢 Using Generated Codes</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Select an account from the list</li>
                    <li>Current 6-digit code displays in large text</li>
                    <li>Countdown timer shows seconds until next refresh</li>
                    <li>Click "Copy Code to Clipboard" for easy pasting</li>
                    <li>Codes automatically update every 30 seconds</li>
                </ul>
            </div>

            <h2 style="color: #1abc9c; border-bottom: 2px solid #1abc9c; padding-bottom: 5px;">👁️ Visual Indicators</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Progress bar shows time remaining (green → yellow → red)</li>
                    <li>Large, easy-to-read monospace font for codes</li>
                    <li>Clear countdown text showing refresh time</li>
                    <li>Copy button changes to "Copied!" for confirmation</li>
                </ul>
            </div>

            <h2 style="color: #e67e22; border-bottom: 2px solid #e67e22; padding-bottom: 5px;">⚙️ Account Management</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>View all your 2FA accounts in organized list</li>
                    <li>Delete accounts you no longer need</li>
                    <li>Accounts persist between application restarts</li>
                    <li>Secure local storage (not cloud-synced)</li>
                </ul>
            </div>

            <h2 style="color: #8e44ad; border-bottom: 2px solid #8e44ad; padding-bottom: 5px;">🔒 Security Notes</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Secret keys are stored locally on your device</li>
                    <li>No internet connection required for code generation</li>
                    <li>Codes are generated using industry-standard TOTP algorithm</li>
                    <li>Same codes as Google Authenticator, Authy, etc.</li>
                </ul>
            </div>

            <h2 style="color: #16a085; border-bottom: 2px solid #16a085; padding-bottom: 5px;">🌐 Supported Services</h2>

            <div style="margin: 20px 0;">
                <p>Works with any service that supports TOTP 2FA:</p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Google/Gmail accounts</li>
                    <li>GitHub</li>
                    <li>Discord</li>
                    <li>Microsoft accounts</li>
                    <li>Banking websites</li>
                    <li>Social media platforms</li>
                    <li>And many more</li>
                </ul>
            </div>

            <h2 style="color: #d35400; border-bottom: 2px solid #d35400; padding-bottom: 5px;">📋 Workflow Example</h2>

            <div style="margin: 20px 0;">
                <ol style="margin: 10px 0; padding-left: 25px;">
                    <li>Enable 2FA on GitHub</li>
                    <li>Copy the secret key from GitHub's setup page</li>
                    <li>Add account in Jasmine's 2FA Manager</li>
                    <li>When logging into GitHub, select the account</li>
                    <li>Copy the current 6-digit code</li>
                    <li>Paste into GitHub's 2FA prompt</li>
                </ol>
            </div>

            <h2 style="color: #7b1fa2; border-bottom: 2px solid #7b1fa2; padding-bottom: 5px;">💡 Benefits Over Mobile Apps</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Access codes directly on your computer</li>
                    <li>No need to grab your phone</li>
                    <li>Larger, easier-to-read display</li>
                    <li>Integrated with your browsing workflow</li>
                    <li>Quick clipboard copying</li>
                </ul>
            </div>

            <h2 style="color: #388e3c; border-bottom: 2px solid #388e3c; padding-bottom: 5px;">⏰ Time Synchronization</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Codes are time-based (30-second intervals)</li>
                    <li>Uses your system clock for accuracy</li>
                    <li>Same timing as other authenticator apps</li>
                    <li>Automatic refresh every second</li>
                </ul>
            </div>

            <div style="background-color: #d1ecf1; padding: 15px; border-radius: 8px; margin: 25px 0;">
                <h3 style="color: #0c5460; margin-top: 0;">🌟 Integrated Security</h3>
                <p style="margin-bottom: 0;">This 2FA manager eliminates the need for separate authenticator apps while providing the same security benefits, making it convenient to access your two-factor codes directly within Jasmine.</p>
            </div>
        </div>
    )";
}

QString HelpMenuDialog::getDataManagementContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;">
            <h1 style="color: #e74c3c; text-align: center; margin-bottom: 20px;">🗂️ Data Management & Privacy</h1>

            <div style="background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin-bottom: 25px;">
                <h2 style="color: #2c3e50; margin-top: 0;">Session & Profile Data Management</h2>
                <p>Jasmine provides comprehensive tools to manage your browsing data, sessions, and privacy settings. Control what data is stored and when to clear it.</p>
            </div>

            <h2 style="color: #3498db; border-bottom: 2px solid #3498db; padding-bottom: 5px;">🧹 Clean Current Session Data</h2>

            <div style="margin: 20px 0;">
                <p><strong>What it does:</strong></p>
                <p>Clears browsing data from all currently active sessions and the shared profile.</p>

                <p><strong>Data removed:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>All cookies from active sessions</li>
                    <li>HTTP cache from all profiles</li>
                    <li>Visited links history</li>
                    <li>Temporary browsing data</li>
                </ul>

                <p><strong>When to use:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>After browsing sensitive websites</li>
                    <li>When sharing your computer</li>
                    <li>To free up storage space</li>
                    <li>For privacy after online shopping/banking</li>
                </ul>
            </div>

            <h2 style="color: #27ae60; border-bottom: 2px solid #27ae60; padding-bottom: 5px;">👥 Clean Shared Profile Data</h2>

            <div style="margin: 20px 0;">
                <p><strong>What it does:</strong></p>
                <p>Clears browsing data only from the shared profile, leaving separate tab profiles untouched.</p>

                <p><strong>Data removed:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Shared profile cookies only</li>
                    <li>Shared profile cache</li>
                    <li>Shared profile visited links</li>
                </ul>

                <p><strong>What's preserved:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Individual tab profile data</li>
                    <li>Private profile sessions</li>
                    <li>Separate profile cookies and cache</li>
                </ul>

                <p><strong>When to use:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>When you want to keep private profiles intact</li>
                    <li>To clear general browsing without affecting work profiles</li>
                    <li>Selective privacy cleaning</li>
                </ul>
            </div>

            <h2 style="color: #e74c3c; border-bottom: 2px solid #e74c3c; padding-bottom: 5px;">🏭 Restore Factory Defaults</h2>

            <div style="margin: 20px 0;">
                <p><strong>What it does:</strong></p>
                <p>Completely resets Jasmine to its original state, removing all user data and settings.</p>

                <p><strong>Data removed:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>All saved websites and bookmarks</li>
                    <li>All saved sessions</li>
                    <li>All application settings and preferences</li>
                    <li>Security settings and master passwords</li>
                    <li>All browsing data (cookies, cache, history)</li>
                    <li>Application data directories</li>
                    <li>Profile configurations</li>
                </ul>
            </div>

            <div style="background-color: #f8d7da; padding: 15px; border-radius: 8px; margin: 15px 0; border-left: 4px solid #dc3545;">
                <h3 style="color: #721c24; margin-top: 0;">⚠️ Factory Reset Warning</h3>
                <p style="margin-bottom: 0;"><strong>This action cannot be undone!</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>All your saved data will be permanently lost</li>
                    <li>Application will close automatically after reset</li>
                    <li>You'll need to restart Jasmine manually</li>
                    <li>All customizations will be lost</li>
                </ul>
            </div>

            <h2 style="color: #f39c12; border-bottom: 2px solid #f39c12; padding-bottom: 5px;">📍 How to Access These Features</h2>

            <div style="margin: 20px 0;">
                <p>All data management options are located in the <strong>Sessions</strong> menu:</p>
                <ol style="margin: 10px 0; padding-left: 25px;">
                    <li>Click on "Sessions" in the menu bar</li>
                    <li>Scroll to the bottom section</li>
                    <li>Choose your desired cleaning option</li>
                    <li>Confirm the action in the dialog box</li>
                </ol>
            </div>

            <h2 style="color: #9b59b6; border-bottom: 2px solid #9b59b6; padding-bottom: 5px;">🔄 Data Types Explained</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #8e44ad;">Cookies</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Login sessions and preferences</li>
                    <li>Shopping cart contents</li>
                    <li>Website customizations</li>
                </ul>

                <h3 style="color: #8e44ad;">HTTP Cache</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Temporarily stored website files</li>
                    <li>Images, scripts, and stylesheets</li>
                    <li>Speeds up repeat visits</li>
                </ul>

                <h3 style="color: #8e44ad;">Visited Links</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>History of visited websites</li>
                    <li>Link color changes (visited vs unvisited)</li>
                    <li>Navigation history</li>
                </ul>
            </div>

            <h2 style="color: #1abc9c; border-bottom: 2px solid #1abc9c; padding-bottom: 5px;">🛡️ Privacy Recommendations</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #16a085;">Regular Cleaning (Weekly)</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Use "Clean Shared Profile Data" for routine maintenance</li>
                    <li>Keeps private profiles intact</li>
                    <li>Maintains good performance</li>
                </ul>

                <h3 style="color: #16a085;">Deep Cleaning (Monthly)</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Use "Clean Current Session Data" for thorough cleanup</li>
                    <li>Clears all active session data</li>
                    <li>Good for privacy and storage</li>
                </ul>

                <h3 style="color: #16a085;">Emergency Cleaning</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>After using public computers</li>
                    <li>When selling or giving away device</li>
                    <li>After security concerns</li>
                </ul>
            </div>

            <h2 style="color: #e67e22; border-bottom: 2px solid #e67e22; padding-bottom: 5px;">💡 Smart Usage Tips</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Before cleaning:</strong> Save any important sessions you want to keep</li>
                    <li><strong>Profile separation:</strong> Use private profiles for sensitive browsing</li>
                    <li><strong>Regular maintenance:</strong> Clean shared profile weekly, all data monthly</li>
                    <li><strong>Factory reset:</strong> Only use when starting completely fresh</li>
                    <li><strong>Backup important data:</strong> Export sessions before major cleaning</li>
                </ul>
            </div>

            <h2 style="color: #8e44ad; border-bottom: 2px solid #8e44ad; padding-bottom: 5px;">⚡ Performance Benefits</h2>

            <div style="margin: 20px 0;">
                <p><strong>Regular data cleaning provides:</strong></p>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Faster application startup</li>
                    <li>Reduced memory usage</li>
                    <li>More available storage space</li>
                    <li>Improved browsing performance</li>
                    <li>Better privacy protection</li>
                </ul>
            </div>

            <div style="background-color: #d1ecf1; padding: 15px; border-radius: 8px; margin: 25px 0;">
                <h3 style="color: #0c5460; margin-top: 0;">🎯 Choose the Right Tool</h3>
                <p style="margin-bottom: 0;">
                    <strong>Shared Profile Clean:</strong> For routine maintenance<br>
                    <strong>Current Session Clean:</strong> For thorough privacy cleaning<br>
                    <strong>Factory Reset:</strong> For complete fresh start
                </p>
            </div>
        </div>
    )";
}

QString HelpMenuDialog::getDownloadManagerContent()
{
    return R"(
        <div style="font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;">
            <h1 style="color: #e74c3c; text-align: center; margin-bottom: 20px;">📥 Download Manager</h1>

            <div style="background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin-bottom: 25px;">
                <h2 style="color: #2c3e50; margin-top: 0;">Integrated Download Management</h2>
                <p>Jasmine includes a comprehensive download manager that handles all your file downloads with progress tracking, organization, and easy access to downloaded files.</p>
            </div>

            <h2 style="color: #3498db; border-bottom: 2px solid #3498db; padding-bottom: 5px;">🚀 Key Features</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Real-time download progress tracking</li>
                    <li>Download speed and time remaining calculations</li>
                    <li>Automatic file organization in dedicated folder</li>
                    <li>Duplicate filename handling</li>
                    <li>One-click access to files and folders</li>
                    <li>Download history management</li>
                    <li>Cancel active downloads</li>
                    <li>Clean interface with visual progress bars</li>
                </ul>
            </div>

            <h2 style="color: #27ae60; border-bottom: 2px solid #27ae60; padding-bottom: 5px;">📍 How to Access Downloads</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #229954;">Opening the Download Manager</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Click the <strong>Downloads</strong> icon in the toolbar</li>
                    <li>Or go to <strong>View → Downloads</strong> in the menu</li>
                    <li>Download window opens showing all current and past downloads</li>
                </ul>

                <h3 style="color: #229954;">Download Location</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Files are saved to: <code>Downloads/Jasmine/</code></li>
                    <li>Organized in your system's default Downloads folder</li>
                    <li>Automatic folder creation if it doesn't exist</li>
                </ul>
            </div>

            <h2 style="color: #f39c12; border-bottom: 2px solid #f39c12; padding-bottom: 5px;">📊 Download Progress Tracking</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #d68910;">Real-time Information</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>File name and size:</strong> Clear identification of what's downloading</li>
                    <li><strong>Progress bar:</strong> Visual representation of download completion</li>
                    <li><strong>Speed indicator:</strong> Current download speed (KB/s, MB/s)</li>
                    <li><strong>Time remaining:</strong> Estimated completion time</li>
                    <li><strong>Status updates:</strong> Starting, downloading, completed, cancelled</li>
                </ul>

                <h3 style="color: #d68910;">Progress Display</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Percentage completion with visual progress bar</li>
                    <li>Downloaded size vs. total file size</li>
                    <li>Dynamic speed calculations updated every second</li>
                    <li>Color-coded status indicators</li>
                </ul>
            </div>

            <h2 style="color: #9b59b6; border-bottom: 2px solid #9b59b6; padding-bottom: 5px;">🎛️ Download Controls</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #8e44ad;">During Download</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Cancel Button:</strong> Stop active downloads immediately</li>
                    <li><strong>Open Folder:</strong> Access download directory anytime</li>
                    <li><strong>Progress Monitoring:</strong> Watch real-time progress</li>
                </ul>

                <h3 style="color: #8e44ad;">After Download</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Open File:</strong> Launch downloaded file directly</li>
                    <li><strong>Open Folder:</strong> Navigate to file location</li>
                    <li><strong>Remove from List:</strong> Clean up download history</li>
                </ul>
            </div>

            <h2 style="color: #1abc9c; border-bottom: 2px solid #1abc9c; padding-bottom: 5px;">🗂️ File Organization</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #16a085;">Automatic Organization</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>All downloads saved to dedicated Jasmine folder</li>
                    <li>Automatic duplicate filename handling</li>
                    <li>Files renamed with numbers: <code>file.pdf</code>, <code>file (1).pdf</code>, <code>file (2).pdf</code></li>
                    <li>Preserves original file extensions</li>
                </ul>

                <h3 style="color: #16a085;">Smart Naming</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Uses original filename from website</li>
                    <li>Fallback to "download" if no name available</li>
                    <li>Prevents file overwrites automatically</li>
                </ul>
            </div>

            <h2 style="color: #e67e22; border-bottom: 2px solid #e67e22; padding-bottom: 5px;">🧹 Download Management</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #d35400;">Window Controls</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Clear Finished:</strong> Remove completed/cancelled downloads from list</li>
                    <li><strong>Open Downloads Folder:</strong> Quick access to download directory</li>
                    <li><strong>Individual Remove:</strong> Remove specific items from history</li>
                </ul>

                <h3 style="color: #d35400;">List Management</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Chronological list of all downloads</li>
                    <li>Persistent across application restarts</li>
                    <li>Easy cleanup of old downloads</li>
                    <li>Empty state message when no downloads</li>
                </ul>
            </div>

            <h2 style="color: #8e44ad; border-bottom: 2px solid #8e44ad; padding-bottom: 5px;">💡 Download States</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #7b1fa2;">Active Downloads</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Starting:</strong> Download initializing</li>
                    <li><strong>In Progress:</strong> Actively downloading with progress</li>
                    <li><strong>Speed Display:</strong> Real-time transfer rate</li>
                    <li><strong>Cancel Option:</strong> Stop button available</li>
                </ul>

                <h3 style="color: #7b1fa2;">Completed Downloads</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Completed:</strong> Successfully downloaded</li>
                    <li><strong>Cancelled:</strong> User stopped download</li>
                    <li><strong>Interrupted:</strong> Network or system error</li>
                    <li><strong>File Access:</strong> Open file/folder buttons available</li>
                </ul>
            </div>

            <h2 style="color: #d32f2f; border-bottom: 2px solid #d32f2f; padding-bottom: 5px;">⚡ Performance Features</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Efficient Memory Usage:</strong> Minimal resource consumption</li>
                    <li><strong>Background Downloads:</strong> Continue while browsing</li>
                    <li><strong>Multiple Downloads:</strong> Handle several files simultaneously</li>
                    <li><strong>Speed Calculation:</strong> Accurate transfer rate monitoring</li>
                    <li><strong>Progress Updates:</strong> Smooth, real-time progress tracking</li>
                </ul>
            </div>

            <h2 style="color: #388e3c; border-bottom: 2px solid #388e3c; padding-bottom: 5px;">🔧 Technical Details</h2>

            <div style="margin: 20px 0;">
                <h3 style="color: #2e7d32;">File Size Formatting</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Automatic unit conversion: B → KB → MB → GB</li>
                    <li>Decimal precision for readability</li>
                    <li>Speed shown as size per second</li>
                </ul>

                <h3 style="color: #2e7d32;">Time Calculations</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li>Remaining time based on current speed</li>
                    <li>Format: seconds, minutes, hours as appropriate</li>
                    <li>Dynamic updates as speed changes</li>
                </ul>
            </div>

            <h2 style="color: #5d4037; border-bottom: 2px solid #5d4037; padding-bottom: 5px;">🎯 Usage Tips</h2>

            <div style="margin: 20px 0;">
                <ul style="margin: 10px 0; padding-left: 20px;">
                    <li><strong>Monitor Progress:</strong> Keep download window open to watch progress</li>
                    <li><strong>Multiple Downloads:</strong> Start several downloads simultaneously</li>
                    <li><strong>Quick Access:</strong> Use "Open Folder" for easy file management</li>
                    <li><strong>Clean History:</strong> Regularly clear finished downloads</li>
                    <li><strong>Cancel if Needed:</strong> Stop unwanted downloads immediately</li>
                    <li><strong>File Organization:</strong> Downloads are automatically organized</li>
                </ul>
            </div>

            <div style="background-color: #fff3cd; padding: 15px; border-radius: 8px; margin: 15px 0;">
                <h3 style="color: #856404; margin-top: 0;">📁 Platform-Specific Notes</h3>
                <p><strong>Flathub Version:</strong> Shows download location in dialog</p>
                <p><strong>Standard Version:</strong> Opens file manager directly</p>
                <p style="margin-bottom: 0;"><strong>All Platforms:</strong> Downloads saved to system Downloads folder under "Jasmine" subdirectory</p>
            </div>

            <div style="background-color: #d1ecf1; padding: 15px; border-radius: 8px; margin: 25px 0;">
                <h3 style="color: #0c5460; margin-top: 0;">🌟 Integrated Experience</h3>
                <p style="margin-bottom: 0;">The download manager seamlessly integrates with your browsing experience, automatically handling all file downloads while providing full control and visibility over the download process.</p>
            </div>
        </div>
    )";
}

QString HelpMenuDialog::getSitesSessionsContent()
{
    return QString(
        "<h3>Managing Sites</h3>"
        "<p><strong>Creating a New Site:</strong></p>"
        "<ul>"
        "<li>Press the <strong>Clear</strong> button to clear existing fields</li>"
        "<li>Fill in the <strong>URL</strong> and <strong>Title</strong> (required fields)</li>"
        "<li>Optionally add <strong>Username</strong>, <strong>Password</strong>, and <strong>Comments</strong></li>"
        "<li>Press the <strong>Add</strong> button to save the site</li>"
        "</ul>"

        "<h3>Managing Sessions</h3>"
        "<p><strong>Creating a New Session:</strong></p>"
        "<ul>"
        "<li>Ensure at least one tab is open in the webview</li>"
        "<li>Select <strong>Save Current Session</strong> from the menu or toolbar</li>"
        "<li>Give your session a name and click <strong>OK</strong></li>"
        "<li>Sessions are automatically assigned a randomly generated SVG icon</li>"
        "</ul>"

        "<h3>Editing Sites and Sessions</h3>"
        "<p><strong>To edit any site or session:</strong></p>"
        "<ul>"
        "<li>Select the item you want to modify</li>"
        "<li>Enter the new values in the appropriate fields</li>"
        "<li>Press the <strong>Update</strong> button to save changes</li>"
        "<li>For sessions: Click the small <strong>Edit</strong> button next to the icon to change it, then click <strong>Update</strong></li>"
        "</ul>"
        );
}

QString HelpMenuDialog::getOnSecurityContent()
{
    return QString(
        "<h3>Security Features Overview</h3>"
        "<p>Jasmine provides several optional security features designed for your convenience. "
        "You are completely free to use or not use any of these features based on your preferences.</p>"

        "<h4>Username & Password Storage</h4>"
        "<ul>"
        "<li>Storing credentials in website entries is <strong>completely optional</strong></li>"
        "<li>Leave these fields blank if you prefer to use your own credentials manager</li>"
        "<li>Stored credentials are saved locally on your device only in binary format</li>"
        "<li>No data is transmitted over the network</li>"
        "</ul>"

        "<h4>Master Password Protection</h4>"
        "<ul>"
        "<li>Optional feature to protect access to Jasmine</li>"
        "<li>When enabled, you'll need to enter your master password on startup</li>"
        "<li>Choose a strong, memorable password and store it safely</li>"
        "<li>If forgotten, you'll need to perform a factory reset</li>"
        "</ul>"

        "<h4>Two-Factor Authentication (2FA) Manager</h4>"
        "<ul>"
        "<li>Optional convenience tool for generating TOTP codes</li>"
        "<li>Helps manage 2FA codes for your various accounts</li>"
        "<li>All secrets are stored locally on your device in binary format</li>"
        "<li>Use only if you're comfortable with local storage</li>"
        "</ul>"

        "<h4>Security Disclaimer</h4>"
        "<p><em>While every reasonable effort has been made to implement a secure framework "
        "and all sensitive info is stored in binary format within Jasmine, "
        "these features are provided as conveniences rather than guarantees. Users are responsible "
        "for deciding what information to store based on their individual security requirements and risk tolerance.</em></p>"

        "<p><strong>Recommendation:</strong> For maximum security, consider using dedicated password managers "
        "and letting your browser handle credential storage.</p>"
        );
}

QString HelpMenuDialog::getOnNewStorageSystemContent() {
    return QString(
        "<h3>New Storage System (Jasmine 1.1.0 and onwards)</h3>"
        "<p>This version of Jasmine uses a new storage system that improves performance and efficiency by using symlinks for profile data. This means that instead of copying entire profile directories, only links are created, saving disk space and speeding up operations.</p>"
        "<h4>Recommendations:</h4>"
        "<p>To fully leverage the new storage system and ensure optimal performance, we highly recommend performing a factory reset. This will clear all old data and provide a clean start. You can find the factory reset option in the 'Sessions' menu.</p>"
        "<h4>Clean up orphaned profile directories on startup:</h4>"
        "<p>As part of the new storage system, a checkbox is available in the 'Tools' menu to automatically clean up unused, orphaned profile directories at application startup. It is STRONGLY RECOMMENDED to keep this option enabled UNLESS you also have old-format sessions saved.</p>"
        "<h4>Handling Old-Format Sessions:</h4>"
        "<p>If you have existing sessions that use the old directory-based storage, you can continue to use them. However, we strongly advise against adding new tabs or saving changes to these older sessions. To ensure optimal performance and avoid potential issues, it's best to create new sessions using the new storage system.</p>"
        );
}

QString HelpMenuDialog::getOnNamedProfilesContent()
{
    return QString(R"(
        <div style="text-align: center; font-family: Arial, sans-serif;">
            <h1 style="color: #2c3e50; margin-bottom: 10px;">Named Shared Profiles</h1>
            <h3 style="color: #7f8c8d; margin-bottom: 20px;">Contextual Browsing Environments</h3>

            <div style="text-align: left; margin: 20px 0; line-height: 1.6;">
                <p>
                    Jasmine's Named Shared Profiles feature takes your browsing organization to the next level by allowing
                    multiple tabs to share the same browsing context under meaningful labels like "Work," "Home," "Shopping,"
                    or "Research." This powerful addition bridges the gap between completely isolated private profiles and a
                    single shared environment.
                </p>

                <div style="background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin: 20px 0;">
                    <h4 style="color: #2c3e50; margin-top: 0;">Examples:</h4>
                    <ul style="margin-left: 20px;">
                        <li><strong>Work Profile:</strong> Company email, project management tools, and internal documentation all share cookies and login states</li>
                        <li><strong>Personal Profile:</strong> Social media and entertainment sites kept separate from work accounts</li>
                        <li><strong>Finance Profile:</strong> Banking, investment, and budgeting tools with shared authentication</li>
                        <li><strong>Travel Profile:</strong> Airline, hotel, and rental car sites that need to exchange booking information</li>
                    </ul>
                </div>

                <p>
                    This contextual grouping maintains the perfect balance between isolation and integration: your work accounts
                    never mix with personal browsing, but related tools within each context can seamlessly communicate when needed.
                    Named Shared Profiles eliminate the all-or-nothing approach to profile isolation, giving you granular control
                    over exactly which tabs should share data with each other while maintaining barriers between different areas of your digital life.
                </p>

                <h3 style="color: #2c3e50; margin-top: 30px;">How to Use Named Profiles</h3>

                <ol style="margin-left: 20px;">
                    <li><strong>Create Profiles:</strong> In the profile area of the toolbar, in the profileSelector combobox select "New Profile..." and give it a meaningful name like "Work" or "Personal"</li>
                    <li><strong>Select a Profile:</strong> Choose your desired profile from the dropdown before launching websites</li>
                    <li><strong>Launch Websites:</strong> Any sites launched while a named profile is selected will share the same browsing context</li>
                    <li><strong>Create Sessions:</strong> Save groups of tabs launched under the same named profile for quick restoration</li>
                    <li><strong>Manage Profiles:</strong> Select "Manage Profiles..." to create, delete, or clean profile data</li>
                </ol>

                <div style="background-color: #e8f4f8; padding: 15px; border-radius: 8px; margin: 20px 0; border-left: 4px solid #3498db;">
                <p><strong>Note:</strong> Keeping the profile selector set to "Default" will use the universal shared profile,
                which is the standard shared browsing environment. Private profiles (toggled per tab via the Private Toggle Button) always remain
                completely isolated regardless of named profile selection.</p>

                <p><strong>Simply put:</strong></p>
                <ul style="margin-left: 20px;">
                    <li>To create tabs with private profile, toggle the Private Profile button ON in the toolbar.
                    This will inactivate the Named Profile selector.</li>
                    <li>To use a named shared profile, untoggle the Private Profile button (if toggled) and select a previously
                    created named shared profile from the combobox.</li>
                    <li>Or leave it set to "Default" to use the universal profile.</li>
                </ul>
                </div>



                <h3 style="color: #2c3e50; margin-top: 30px;">Profile Management</h3>
                <p>
                    You can manage your named profiles by selecting "Manage Profiles..." from the profile selector dropdown. This allows you to:
                </p>
                <ul style="margin-left: 20px;">
                    <li><strong>Create new profiles</strong> for different contexts or projects</li>
                    <li><strong>Delete profiles</strong> you no longer need (only if they're not in use by active sessions)</li>
                    <li><strong>Clean profile data</strong> to remove cookies, cache, and browsing history while keeping the profile</li>
                </ul>

                <p>
                    Each named profile maintains its own separate storage for:
                </p>
                <ul style="margin-left: 20px;">
                    <li>Cookies and login sessions</li>
                    <li>Browsing history and cache</li>
                    <li>Local storage and website data</li>
                    <li>Form data and preferences</li>
                </ul>
            </div>

            <hr style="margin: 30px 0; border: 1px solid #bdc3c7;">

            <div style="margin: 20px 0;">
                <p style="font-size: 14px; color: #7f8c8d;">
                    Organize your digital life with contextual browsing environments
                </p>
            </div>
        </div>
    )");

}

QString HelpMenuDialog::getChangelogContent()
{
    return QString(
        "<div style='font-family: Arial, sans-serif; line-height: 1.6; color: #2c3e50;'>"
        "<h2 style='color: #8e44ad; text-align: center; margin-bottom: 25px;'>📜 Ermis Changelog</h2>"

        "<h4 style='color: #3498db; border-bottom: 2px solid #3498db; padding-bottom: 5px; margin-top: 25px;'>[v1.0.0] - 2026-03-15</h4>"
        "<ul style='margin-bottom: 20px;'>"
        "<li><b>🎉 Initial Release:</b> Ermis Steganography Tool</li>"
        "<li><b>🖼️ Image Steganography:</b> Hide data in PNG, JPG, BMP using LSB techniques with live preview</li>"
        "<li><b>🎵 Audio Steganography:</b> Support for WAV, MP3, FLAC, OGG with FFmpeg conversion</li>"
        "<li><b>📝 Dual Input Modes:</b> Text input and file hiding with filename preservation</li>"
        "<li><b>🔒 AES Encryption:</b> Optional passphrase protection with ENCR marker detection</li>"
        "<li><b>🖱️ Drag & Drop:</b> Intuitive file loading by dragging directly into the application</li>"
        "<li><b>📋 Clipboard Integration:</b> One-click copying of extracted text</li>"
        "<li><b>📊 Capacity Indicator:</b> Real-time display of available hiding space</li>"
        "<li><b>🎚️ Audio Player:</b> Built-in playback controls for loaded audio files</li>"
        "<li><b>🔍 Smart Extraction:</b> Auto-detects encryption, file type, and text content</li>"
        "<li><b>💾 Persistent Paths:</b> Smart directory fallbacks (Pictures → Images, Music → AppDir)</li>"
        "<li><b>🧩 Modular Engine Design:</b> Separate steganography engines for images and audio</li>"
        "<li><b>🌍 Cross-Platform:</b> Available for Linux, Windows, and macOS</li>"
        "</ul>"

        "<div style='background-color: #ecf0f1; padding: 15px; border-radius: 8px; margin: 20px 0; text-align: center;'>"
        "<p style='margin: 0; color: #7f8c8d;'>"
        "<strong>Built with:</strong> Qt 6 Framework + FFmpeg • "
        "<strong>License:</strong> GPL3 • "
        "<strong>Repository:</strong> <a href='https://github.com/alamahant/Ermis'>github.com/alamahant/Ermis</a>"
        "</p>"
        "</div>"

        "<div style='background-color: #f8f9fa; padding: 15px; border-radius: 8px; margin-top: 30px;'>"
        "<h4 style='color: #2c3e50; margin-top: 0;'>🔮 Planned for Future Releases</h4>"
        "<ul style='margin-bottom: 0;'>"
        "<li><b>Video Steganography:</b> Hide data in video files</li>"
        "<li><b>Batch Processing:</b> Hide/extract multiple files at once</li>"
        "<li><b>Steganalysis Tools:</b> Detect hidden data in suspicious files</li>"
        "<li><b>More Encryption Algorithms:</b> Additional cipher options</li>"
        "<li><b>Plugin System:</b> Extensible architecture for custom algorithms</li>"
        "</ul>"
        "</div>"
        "</div>"
    );
}

QString HelpMenuDialog::getSupportusContent()
{
    return QString();

}




