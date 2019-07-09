library(shiny)
library(shinydashboard)
library(shinyjs)
library(googleVis)
library(flexdashboard)
library(DT)


ui2<-(dashboardPage(
  dashboardHeader(title="Martyriser des M1"),
  dashboardSidebar(
    sidebarMenu(id = "tabs",
                menuItem("Questionnaire", tabName = "quest", icon = icon("readme")),
                menuItem("Access Result",tabName = "Ana", icon = icon("poll"))
    )
  ),
  dashboardBody(
    useShinyjs(),
    # Read data
    tabItems(
      tabItem(tabName = "quest",
              div(id="identify",
              wellPanel(textInput("Name", "Nom"),
                        textInput("FirstName","Prénom"),
                        radioButtons(inputId = "Year", 
                                     label = "year",
                                     choices = c("M1" = "M1",
                                                 "M2" = "M2"),
                                     selected = TRUE, inline=T))),
              div(actionButton(inputId = "actBtnVisualisation", label = "Démarrer",icon = icon("play"),#style="color: #fff; background-color: #337ab7; border-color: #2e6da4" 
                               )),
              div(id="Questions", h3(textOutput(outputId = "ZERO")),
                  actionButton(inputId="UN",label = "TEST1",style='height:250px; width:500px;font-size:100%'),
                  actionButton(inputId="DEUX",label = "TEST2",style='height:250px;width:500px; font-size:100%'),
                  actionButton(inputId="TROIS",label = "TEST3",style='height:250px; width:500px;font-size:100%'),
                  actionButton(inputId="QUATRE",label = "TEST4",style='height:250px; width:500px;font-size:100%'),align="center"
                  )
      ),
      tabItem(tabName = "Ana",
              uiOutput("page"))
    ))
))

ui1 <-tagList(
  div(id = "login",
      wellPanel(textInput("userName", "Username"),
                passwordInput("passwd", "Password"),
                br(),actionButton("Login", "Log in"))),
  tags$style(type="text/css", "#login {font-size:10px;   text-align: left;position:absolute;top: 40%;left: 50%;margin-top: -100px;margin-left: -150px;}")
)

ui33 <- fluidPage(column(12,
                        tabBox(title="Analyses des résultats",
                               id="TabAnal",height="800px",width="12",
                          tabPanel("Table"),
                          tabPanel("Summary"),
                          tabPanel("Plot")
)))



server <- shinyServer(function(input,output,session){
  df<-reactiveValues(a=0)
  dataquestions <- reactiveValues()
  hide(id="Questions")
  observeEvent(input$actBtnVisualisation, {
    dataquestions$table = read.csv("test.csv",header=TRUE,sep=",")
    hide(id="identify")
    hide(id="actBtnVisualisation")
    show(id="Questions")
    output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
    updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
    updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
    updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
    updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
    })
  observeEvent((input$UN | input$DEUX | input$TROIS | input$QUATRE), 
               {
                 df$a= df$a  + 1
                 output$ZERO <- renderText({paste(dataquestions$table$QUESTIONS[df$a])})
                 updateActionButton(session,"UN",label=dataquestions$table$REP1[df$a])
                 updateActionButton(session,"DEUX",label=dataquestions$table$REP2[df$a])
                 updateActionButton(session,"TROIS",label=dataquestions$table$REP3[df$a])
                 updateActionButton(session,"QUATRE",label=dataquestions$table$REP4[df$a])
               })
  
  Logged = FALSE;
  my_username <- "Omnia"
  my_password <- "Sakura"
  
  USER <- reactiveValues(Logged=Logged)
  observe({
    if (USER$Logged==FALSE){
      if(!is.null(input$Login)){
        if(input$Login>0){
          
          Username <- isolate(input$userName)
          Password <- isolate(input$passwd)
          Id.username <- which(my_username == Username)
          Id.password <- which(my_password == Password)
          if (length(Id.username) > 0 & length(Id.password) > 0) {
            if (Id.username == Id.password) {
              USER$Logged <- TRUE
            }
          }
        }
      }
    }
  })
  output$page <- renderUI({
    if(USER$Logged){
      return({  div(class="outer",do.call(bootstrapPage,c("",ui33)))  })
      
    }else{
      return({  div(class="outer",do.call(bootstrapPage,c("",ui1)))    })
      
    }
  })
})

shinyApp(ui=ui2,server=server)

